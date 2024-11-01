#include "DatabaseManager.h"
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");            // Замените на ваш хост
    db.setDatabaseName("your_database");     // Замените на имя базы данных
    db.setUserName("your_username");         // Замените на имя пользователя
    db.setPassword("your_password");         // Замените на пароль
}

bool DatabaseManager::open() {
    if (!db.open()) {
        qDebug() << "Не удалось подключиться к базе данных:" << db.lastError().text();
        return false;
    }
    qDebug() << "Подключение к базе данных успешно";
    return true;
}

void DatabaseManager::close() {
    db.close();
}

// CRUD-функция: добавление пользователя
bool DatabaseManager::addUser(const QString& username, const QString& passwordHash, const QString& email, const QString& clientKey) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password_hash, email, client_key) VALUES (:username, :passwordHash, :email, :clientKey)");
    query.bindValue(":username", username);
    query.bindValue(":passwordHash", passwordHash);
    query.bindValue(":email", email);
    query.bindValue(":clientKey", clientKey);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления пользователя:" << query.lastError().text();
        return false;
    }
    return true;
}

// CRUD-функция: получение информации о пользователе
QVariantMap DatabaseManager::getUser(const QString& username) {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", username);

    QVariantMap userInfo;
    if (query.exec() && query.next()) {
        userInfo["id"] = query.value("id");
        userInfo["username"] = query.value("username");
        userInfo["email"] = query.value("email");
        userInfo["client_key"] = query.value("client_key");
        userInfo["is_admin"] = query.value("is_admin");
        userInfo["created_at"] = query.value("created_at");
    } else {
        qDebug() << "Ошибка получения пользователя:" << query.lastError().text();
    }
    return userInfo;
}

// CRUD-функция: обновление пароля пользователя
bool DatabaseManager::updateUserPassword(int userId, const QString& newPasswordHash) {
    QSqlQuery query;
    query.prepare("UPDATE users SET password_hash = :newPasswordHash WHERE id = :userId");
    query.bindValue(":newPasswordHash", newPasswordHash);
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Ошибка обновления пароля пользователя:" << query.lastError().text();
        return false;
    }
    return true;
}

// CRUD-функция: удаление пользователя
bool DatabaseManager::deleteUser(int userId) {
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Ошибка удаления пользователя:" << query.lastError().text();
        return false;
    }
    return true;
}
