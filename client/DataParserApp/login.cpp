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

    // Проверяем, есть ли authManager и вызываем метод логина
    if (authManager) {
        authManager->login(username, password);
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось выполнить вход. authManager не инициализирован.");
    }
}

void Login::sendLoginRequest(const QString &username, const QString &password) {
    QUrl url("https://example.com/api/login"); // Адрес сервера
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("username", username);
    params.addQueryItem("password", password);

    // Подключаем слот для обработки ответа
    connect(networkManager, &QNetworkAccessManager::finished, this, &Login::onLoginFinished);

    // Отправляем запрос POST
    networkManager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
}

void Login::onLoginFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QString token = reply->readAll(); // Обработка успешного ответа
        AuthManager::saveToken(token);
        QMessageBox::information(this, "Успех", "Авторизация успешна!");
    } else {
        QMessageBox::warning(this, "Ошибка", "Ошибка авторизации.");
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
