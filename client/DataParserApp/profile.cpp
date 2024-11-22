#include "profile.h"
#include "qstackedwidget.h"
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

Profile::Profile(QWidget *parent) : QWidget(parent) {
    // Основная компоновка страницы
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Горизонтальная компоновка для размещения кнопки слева
    QHBoxLayout *topLayout = new QHBoxLayout;

    // Создаем кнопку "Назад на главную"
    QPushButton *backToHomeButton = new QPushButton("Назад на главную", this);
    backToHomeButton->setStyleSheet("background-color: white; color: black;"); // Устанавливаем стиль кнопки

    // Подключаем слот для обработки нажатия
    connect(backToHomeButton, &QPushButton::clicked, this, &Profile::onBackToHomeButtonClicked);

    // Добавляем кнопку в левую часть горизонтальной компоновки
    topLayout->addWidget(backToHomeButton, 0, Qt::AlignLeft);

    // Добавляем отступ в правую часть горизонтальной компоновки, чтобы кнопка оставалась слева
    topLayout->addStretch();

    // Добавляем горизонтальную компоновку в основную вертикальную
    layout->addLayout(topLayout);

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText("Введите описание заказа...");
    descriptionEdit->setStyleSheet("background-color: white; color: black;");
    layout->addWidget(descriptionEdit);

    // Поле для загрузки файлов
    QPushButton *uploadFilesButton = new QPushButton("Загрузить файлы", this);
    uploadFilesButton->setStyleSheet("background-color: lightblue; color: black;");
    connect(uploadFilesButton, &QPushButton::clicked, [this]() {
        QStringList fileNames = QFileDialog::getOpenFileNames(this, "Выберите файлы", QString(), "CSV Files (*.csv);;JSON Files (*.json)");
        if (!fileNames.isEmpty()) {
            QMessageBox::information(this, "Файлы загружены", "Выбранные файлы: " + fileNames.join(", "));
        }
    });
    layout->addWidget(uploadFilesButton);

    submitButton = new QPushButton("Отправить заказ", this);
    submitButton->setStyleSheet("background-color: lightblue; color: black;");
    connect(submitButton, &QPushButton::clicked, this, &Profile::onSubmitButtonClicked);
    layout->addWidget(submitButton);

    setLayout(layout);
}

void Profile::onSubmitButtonClicked() {
    QString description = descriptionEdit->toPlainText();
    if (description.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите описание заказа.");
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"description\""));
    textPart.setBody(description.toUtf8());

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"config.json\""));
    QFile *file = new QFile("/path/to/config.json");  // Укажите путь к файлу
    if (!file->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        delete multiPart;
        return;
    }
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(textPart);
    multiPart->append(filePart);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://example.com/api/upload"));

    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply); // multiPart удалится вместе с reply

    connect(reply, &QNetworkReply::finished, this, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QMessageBox::information(nullptr, "Успех", "Файл успешно отправлен!");
        } else {
            QMessageBox::warning(nullptr, "Ошибка", "Ошибка при отправке файла.");
        }
        reply->deleteLater();
    });
}

// Слот для кнопки возврата на главную страницу
void Profile::onBackToHomeButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0); // Переключаемся на главную страницу
    }
}
