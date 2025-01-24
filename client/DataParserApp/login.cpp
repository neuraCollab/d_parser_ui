#include "login.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "qstackedwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>


Login::Login(QWidget *parent) : QWidget(parent), authManager(nullptr) {
    // Инициализация QNetworkAccessManager
    networkManager = new QNetworkAccessManager(this);

    // Основная компоновка страницы
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Горизонтальная компоновка для размещения кнопки слева
    QHBoxLayout *topLayout = new QHBoxLayout;

    // Создаем кнопку "Назад на главную"
    QPushButton *backToHomeButton = new QPushButton("Назад на главную", this);
    backToHomeButton->setStyleSheet("background-color: white; color: black;"); // Устанавливаем стиль кнопки

    // Подключаем слот для обработки нажатия
    connect(backToHomeButton, &QPushButton::clicked, this, &Login::onBackToHomeButtonClicked);

    // Добавляем кнопку в левую часть горизонтальной компоновки
    topLayout->addWidget(backToHomeButton, 0, Qt::AlignLeft);

    // Добавляем отступ в правую часть горизонтальной компоновки, чтобы кнопка оставалась слева
    topLayout->addStretch();

    // Добавляем горизонтальную компоновку в основную вертикальную
    layout->addLayout(topLayout);

    // Поле ввода имени пользователя
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Username");
    usernameEdit->setStyleSheet("background-color: white; color: black;"); // Устанавливаем стиль поля ввода
    layout->addWidget(usernameEdit);

    // Поле ввода пароля
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet("background-color: white; color: black;"); // Устанавливаем стиль поля ввода
    layout->addWidget(passwordEdit);

    // Кнопка входа
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    loginButton = new QPushButton("Login", this);
    loginButton->setStyleSheet("background-color: lightblue; color: darkblue;");
    loginButton->setFixedSize(100, 30);
    buttonLayout->addStretch();         // Отступ слева
    buttonLayout->addWidget(loginButton, 0, Qt::AlignCenter); // Центрируем кнопку
    buttonLayout->addStretch();         // Отступ справа
    layout->addWidget(loginButton);

    // Подключаем сигнал для кнопки входа
    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginButtonClicked);

    setLayout(layout);
}

void Login::setAuthManager(AuthManager *authManager) {
    this->authManager = authManager;
}

void Login::onLoginButtonClicked() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Имя пользователя и пароль не должны быть пустыми.");
        return;
    }

    sendLoginRequest(username, password);
}

void Login::sendLoginRequest(const QString &username, const QString &password) {
    QUrl url("http://localhost:8080/login"); // Адрес вашего сервера
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Подготовка JSON-данных для отправки
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;

    QJsonDocument jsonDoc(json);




    // Подключаем слот для обработки ответа
    connect(networkManager, &QNetworkAccessManager::finished, this, &Login::onLoginFinished);

    // Отправляем запрос POST
    networkManager->post(request, jsonDoc.toJson());

}

void Login::onLoginFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        // Обработка успешного ответа
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject responseObject = jsonResponse.object();

        if (responseObject.contains("token")) {
            QString token = responseObject["token"].toString();
            QString role = responseObject["role"].toString();

             qDebug() << "Loaded Token:" << token;

            AuthManager::saveToken(token); // Сохранение токена (реализация в AuthManager)
            QMessageBox::information(this, "Успех", QString("Авторизация успешна! Ваша роль: %1").arg(role));
        } else {
            QMessageBox::warning(this, "Ошибка", "Ответ сервера не содержит токена.");
        }

        qDebug() << "Saved Token:" << AuthManager::instance().getToken();

    } else {
        // Обработка ошибки
        QMessageBox::warning(this, "Ошибка", QString("Ошибка авторизации: %1").arg(reply->errorString()));
    }

    reply->deleteLater();
}

// Слот для кнопки возврата на главную страницу
void Login::onBackToHomeButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0); // Переключаемся на главную страницу
    }
}
