#include "authmanager.h"
#include <QSettings>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QMessageBox>

AuthManager &AuthManager::instance() {
    static AuthManager instance; // Единственный экземпляр
    return instance;
}

AuthManager::AuthManager(QObject *parent)
    : QObject(parent), isAuthenticated(false) {
    networkManager = new QNetworkAccessManager(this);

    // Загружаем токен из настроек при инициализации
    jwtToken = loadToken();
    isAuthenticated = !jwtToken.isEmpty();

    // Отладка
    qDebug() << "Loaded token during initialization:" << jwtToken;
}

void AuthManager::login(const QString &username, const QString &password) {
    QUrl url("http://localhost:8080/login"); // URL вашего сервера
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Создаем JSON для отправки
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;

    // Отправляем POST-запрос
    QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &AuthManager::onLoginReply);
}

void AuthManager::onLoginReply() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    if (reply->error() == QNetworkReply::NoError) {
        // Парсим ответ JSON и сохраняем токен
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObject = jsonResponse.object();
        QString token = jsonObject.value("token").toString();
        QString role = jsonObject.value("role").toString();

        if (!token.isEmpty()) {
            setToken(token);
            saveToken(token); // Сохраняем токен локально
            isAuthenticated = true;
            emit loginSuccess(role); // Передаём роль пользователя

            // Отладка
            qDebug() << "Token successfully saved:" << token;
        } else {
            emit loginFailed("Токен не был получен.");
        }
    } else {
        emit loginFailed(reply->errorString());
    }

    reply->deleteLater();
}

void AuthManager::setToken(const QString &token) {
    jwtToken = token;
}

QString AuthManager::getToken() const {
    return jwtToken;
}

void AuthManager::saveToken(const QString &token) {
    QSettings settings("MyCompany", "MyApp"); // Указываем уникальные параметры
    settings.setValue("auth/token", token);
    settings.sync(); // Принудительно записать изменения в хранилище

    // Отладочное сообщение для проверки
    qDebug() << "Token saved:" << token;
}

QString AuthManager::loadToken() {
    QSettings settings("MyCompany", "MyApp"); // Указываем уникальные параметры
    QString token = settings.value("auth/token", "").toString();

    // Отладка
    qDebug() << "Loaded token:" << token;
    return token;
}

bool AuthManager::isUserAuthenticated() const {
    QString token = loadToken(); // Загружаем токен каждый раз для проверки
    return !token.isEmpty();
}

void AuthManager::clearToken() {
    QSettings settings("MyCompany", "MyApp"); // Указываем уникальные параметры
    settings.remove("auth/token");
    settings.sync(); // Принудительная запись изменений
    jwtToken.clear();
    isAuthenticated = false;

    // Отладка
    qDebug() << "Token cleared.";
}

void AuthManager::logout() {
    clearToken();
    emit loggedOut();
}
