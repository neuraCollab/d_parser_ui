#include "SessionManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QDebug>

QString SessionManager::generateToken(const QString& username) {
    QString rawData = username + QString::number(QDateTime::currentMSecsSinceEpoch());
    QByteArray hashedData = QCryptographicHash::hash(rawData.toUtf8(), QCryptographicHash::Sha256);
    return hashedData.toHex();
}

// Создание сессии
bool SessionManager::createSession(int userId, const QString& token, const QDateTime& expiresAt) {
    QSqlQuery query;
    query.prepare("INSERT INTO sessions (user_id, token, expires_at) VALUES (:userId, :token, :expiresAt)");
    query.bindValue(":userId", userId);
    query.bindValue(":token", token);
    query.bindValue(":expiresAt", expiresAt);

    if (!query.exec()) {
        qDebug() << "Ошибка создания сессии:" << query.lastError().text();
        return false;
    }
    return true;
}

// Получение сессии по токену
QVariantMap SessionManager::getSession(const QString& token) {
    QSqlQuery query;
    query.prepare("SELECT * FROM sessions WHERE token = :token AND expires_at > NOW()");
    query.bindValue(":token", token);

    QVariantMap sessionInfo;
    if (query.exec() && query.next()) {
        sessionInfo["user_id"] = query.value("user_id");
        sessionInfo["expires_at"] = query.value("expires_at");
    } else {
        qDebug() << "Сессия не найдена или истекла:" << query.lastError().text();
    }
    return sessionInfo;
}

// Удаление сессии
bool SessionManager::deleteSession(const QString& token) {
    QSqlQuery query;
    query.prepare("DELETE FROM sessions WHERE token = :token");
    query.bindValue(":token", token);

    if (!query.exec()) {
        qDebug() << "Ошибка удаления сессии:" << query.lastError().text();
        return false;
    }
    return true;
}
