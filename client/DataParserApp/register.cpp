#include "register.h"
#include "qstackedwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRegularExpression>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

Register::Register(QWidget *parent) : QWidget(parent) {
    // Инициализация QNetworkAccessManager
    networkManager = new QNetworkAccessManager(this);

    // Основная компоновка страницы
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Горизонтальная компоновка для размещения кнопки слева
    QHBoxLayout *topLayout = new QHBoxLayout;

    // Создаем кнопку "Назад на главную"
    QPushButton *backToHomeButton = new QPushButton("Назад на главную", this);
    backToHomeButton->setStyleSheet("background-color: white; color: black;");

    // Подключаем слот для обработки нажатия
    connect(backToHomeButton, &QPushButton::clicked, this, &Register::onBackToHomeButtonClicked);

    // Добавляем кнопку в левую часть горизонтальной компоновки
    topLayout->addWidget(backToHomeButton, 0, Qt::AlignLeft);

    // Добавляем отступ в правую часть горизонтальной компоновки, чтобы кнопка оставалась слева
    topLayout->addStretch();

    // Добавляем горизонтальную компоновку в основную вертикальную
    layout->addLayout(topLayout);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Ваше имя");
    nameEdit->setStyleSheet("background-color: white; color: black;");
    layout->addWidget(nameEdit);

    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Email");
    emailEdit->setStyleSheet("background-color: white; color: black;");
    layout->addWidget(emailEdit);

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet("background-color: white; color: black;");
    layout->addWidget(passwordEdit);

    registerButton = new QPushButton("Зарегистрироваться", this);
    registerButton->setStyleSheet("background-color: lightblue; color: darkblue;");
    layout->addWidget(registerButton);

    connect(registerButton, &QPushButton::clicked, this, &Register::onRegisterButtonClicked);

    setLayout(layout);
}

void Register::onRegisterButtonClicked() {
    QString email = emailEdit->text();
    QString password = passwordEdit->text();
    QString name = nameEdit->text();

    // Проверка условий
    if (email.isEmpty() || password.isEmpty() || name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля.");
        return;
    }

    // Проверка email
    QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный email.");
        return;
    }

    // Проверка пароля
    if (password.length() < 4 || !password.contains(QRegularExpression("[0-9]")) || !password.contains(QRegularExpression("[a-zA-Z]"))) {
        QMessageBox::warning(this, "Ошибка", "Пароль должен содержать минимум 4 символа, включая хотя бы одну цифру и букву.");
        return;
    }

    // Отправка запроса на сервер
    sendRegisterRequest(name, email, password);
}

void Register::sendRegisterRequest(const QString &name, const QString &email, const QString &password) {
    QUrl url("http://localhost:8080/register"); // Адрес сервера
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Подготовка JSON-данных для отправки
    QJsonObject json;
    json["username"] = name;
    json["password"] = password;
    json["role"] = "user"; // Роль задаётся по умолчанию

    QJsonDocument jsonDoc(json);

    // Подключаем обработчик ответа
    connect(networkManager, &QNetworkAccessManager::finished, this, &Register::onRegisterFinished);

    // Отправляем запрос POST
    networkManager->post(request, jsonDoc.toJson());
}

void Register::onRegisterFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        // Обработка успешного ответа
        QString response = reply->readAll();
        QMessageBox::information(this, "Успех", response);
    } else {
        // Обработка ошибки
        QMessageBox::warning(this, "Ошибка", QString("Ошибка регистрации: %1").arg(reply->errorString()));
    }

    reply->deleteLater();
}

// Слот для кнопки возврата на главную страницу
void Register::onBackToHomeButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0); // Переключаемся на главную страницу
    }
}
