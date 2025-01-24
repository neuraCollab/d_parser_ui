#include "profile.h"
#include "authmanager.h"
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

    // Горизонтальная компоновка для размещения кнопок
    QHBoxLayout *topLayout = new QHBoxLayout;

    // Создаем кнопку "Назад на главную"
    backToHomeButton = new QPushButton("Назад на главную", this);
    backToHomeButton->setStyleSheet("background-color: white; color: black;");
    connect(backToHomeButton, &QPushButton::clicked, this, &Profile::onBackToHomeButtonClicked);

    // Добавляем кнопку "Выход"
    QPushButton *logoutButton = new QPushButton("Выйти", this);
    logoutButton->setStyleSheet("background-color: red; color: white;");
    connect(logoutButton, &QPushButton::clicked, this, &Profile::onLogoutButtonClicked);

    // Добавляем кнопки в верхнюю панель
    topLayout->addWidget(backToHomeButton, 0, Qt::AlignLeft);
    topLayout->addStretch();
    topLayout->addWidget(logoutButton, 0, Qt::AlignRight);

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

// Слот для кнопки выхода
void Profile::onLogoutButtonClicked() {
    AuthManager::instance().logout(); // Вызываем logout из AuthManager
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget *>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0); // Переключаемся на главную страницу после выхода
    }
}
