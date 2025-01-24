#include "profile.h"
#include <QStackedWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

Profile::Profile(QWidget *parent)
    : QWidget(parent), networkManager(new QNetworkAccessManager(this)) {
    // Основная компоновка страницы
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Горизонтальная компоновка для размещения кнопки слева
    QHBoxLayout *topLayout = new QHBoxLayout;

    // Создаем кнопку "Назад на главную"
    backToHomeButton = new QPushButton("Назад на главную", this);
    backToHomeButton->setStyleSheet("background-color: white; color: black;");

    // Подключаем слот для обработки нажатия
    connect(backToHomeButton, &QPushButton::clicked, this, &Profile::onBackToHomeButtonClicked);

    // Добавляем кнопку в левую часть горизонтальной компоновки
    topLayout->addWidget(backToHomeButton, 0, Qt::AlignLeft);

    // Добавляем отступ в правую часть горизонтальной компоновки, чтобы кнопка оставалась слева
    topLayout->addStretch();

    // Добавляем горизонтальную компоновку в основную вертикальную
    layout->addLayout(topLayout);

    // Поле для ввода описания заказа
    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText("Введите описание заказа...");
    descriptionEdit->setStyleSheet("background-color: white; color: black;");
    layout->addWidget(descriptionEdit);

    // Поле для выбора файлов
    QPushButton *uploadFilesButton = new QPushButton("Выбрать файлы", this);
    uploadFilesButton->setStyleSheet("background-color: lightblue; color: black;");
    connect(uploadFilesButton, &QPushButton::clicked, this, &Profile::onSelectFiles);
    layout->addWidget(uploadFilesButton);

    // Кнопка отправки заказа
    submitButton = new QPushButton("Отправить заказ", this);
    submitButton->setStyleSheet("background-color: lightblue; color: black;");
    connect(submitButton, &QPushButton::clicked, this, &Profile::onSubmitButtonClicked);
    layout->addWidget(submitButton);

    setLayout(layout);
}

void Profile::onSelectFiles() {
    selectedFiles = QFileDialog::getOpenFileNames(this, "Выберите файлы", QString(), "Все файлы (*.*)");
    if (selectedFiles.isEmpty()) {
        QMessageBox::information(this, "Файлы не выбраны", "Выберите хотя бы один файл.");
    } else {
        QMessageBox::information(this, "Файлы выбраны", "Выбранные файлы: " + selectedFiles.join(", "));
    }
}

void Profile::onSubmitButtonClicked() {
    QString description = descriptionEdit->toPlainText();
    if (description.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите описание заказа.");
        return;
    }

    if (selectedFiles.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите хотя бы один файл для загрузки.");
        return;
    }

    sendUploadRequest(description, selectedFiles);
}

void Profile::sendUploadRequest(const QString &description, const QStringList &files) {
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // Добавляем описание заказа
    QHttpPart descriptionPart;
    descriptionPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"description\""));
    descriptionPart.setBody(description.toUtf8());
    multiPart->append(descriptionPart);

    // Добавляем файлы
    for (const QString &filePath : files) {
        QFile *file = new QFile(filePath);
        if (!file->open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл: " + filePath);
            delete multiPart;
            return;
        }

        QHttpPart filePart;
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                           QVariant("form-data; name=\"files\"; filename=\"" + QFileInfo(filePath).fileName() + "\""));
        filePart.setBodyDevice(file);
        file->setParent(multiPart); // Установить multiPart родителем файла, чтобы он автоматически удалился
        multiPart->append(filePart);
    }

    QNetworkRequest request(QUrl("http://localhost:8080/upload")); // Адрес сервера для загрузки файлов
    QNetworkReply *reply = networkManager->post(request, multiPart);
    multiPart->setParent(reply); // multiPart удалится вместе с reply

    connect(reply, &QNetworkReply::finished, this, &Profile::onUploadFinished);
}

void Profile::onUploadFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    if (reply->error() == QNetworkReply::NoError) {
        QMessageBox::information(this, "Успех", "Файлы успешно отправлены!");
    } else {
        QMessageBox::warning(this, "Ошибка", "Ошибка при отправке файлов: " + reply->errorString());
    }
    reply->deleteLater();
}

// Слот для кнопки возврата на главную страницу
void Profile::onBackToHomeButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget *>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0); // Переключаемся на главную страницу
    }
}
