#include "authmanager.h"
#include "qsettings.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QMessageBox>

AuthManager::AuthManager(QObject *parent) : QObject(parent), isAuthenticated(false) {
    networkManager = new QNetworkAccessManager(this);
}

void AuthManager::login(const QString &username, const QString &password) {
    QUrl url("http://server.url/api/login");
    QNetworkRequest request(url);

    // Создаем JSON для отправки
    QJsonObject json;
    json["username"] = username;
    json["password"] = password;

    QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &AuthManager::onLoginReply);
}

void AuthManager::onLoginReply() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    if (reply->error() == QNetworkReply::NoError) {
        // Парсим ответ JSON и сохраняем токен
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QString token = jsonResponse.object().value("token").toString();
        setToken(token);
        isAuthenticated = true;
        emit loginSuccess();
    } else {
        emit loginFailed(reply->errorString());
    }
    reply->deleteLater();
}

void AuthManager::setToken(const QString &token) {
    jwtToken = token;
    // Возможно, также стоит сохранить токен в настройках для повторного использования
}

QString AuthManager::getToken() const {
    return jwtToken;
}

void AuthManager::saveToken(const QString &token) {
    QSettings settings;
    settings.setValue("auth/token", token);
}

QString AuthManager::loadToken() {
    QSettings settings;
    return settings.value("auth/token", "").toString();
}

bool AuthManager::isUserAuthenticated() {
    return !loadToken().isEmpty();
}

void AuthManager::clearToken() {
    QSettings settings;
    settings.remove("auth/token");
}
