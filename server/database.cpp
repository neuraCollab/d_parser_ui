#include "database.h"
#include <QDebug>

Database::Database(QObject *parent) : QObject(parent) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open()) {
        qCritical() << "Failed to connect to database:" << db.lastError().text();
    } else {
        qDebug() << "Connected to database.";
        initializeDatabase(); // Инициализация базы данных
    }
}

void Database::initializeDatabase() {
    QSqlQuery query;

    // Создание таблицы пользователей, если она не существует
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            role TEXT NOT NULL
        )
    )";

    if (!query.exec(createTableQuery)) {
        qCritical() << "Failed to create table:" << query.lastError().text();
        return;
    }

    // Проверка наличия начальных данных
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", "admin");
    if (query.exec() && query.next() && query.value(0).toInt() == 0) {
        // Добавление начальных данных
        addUser("admin", hashPassword("admin123"), "admin");
        addUser("user", hashPassword("user123"), "user");
        qDebug() << "Default users added to database.";
    } else {
        qDebug() << "Default users already exist.";
    }
}

bool Database::addUser(const QString &username, const QString &password, const QString &role) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, role) VALUES (:username, :password, :role)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashPassword(password));
    query.bindValue(":role", role);

    if (!query.exec()) {
        qCritical() << "Failed to add user:" << query.lastError().text();
        return false;
    }
    return true;
}

QString Database::hashPassword(const QString &password) {
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

QString Database::getUserRole(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT role FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashPassword(password));

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return QString();
}

QJsonArray Database::getAllUsers() {
    QJsonArray users;
    QSqlQuery query("SELECT id, username, role FROM users");

    while (query.next()) {
        QJsonObject user;
        user["id"] = query.value("id").toInt();
        user["username"] = query.value("username").toString();
        user["role"] = query.value("role").toString();
        users.append(user);
    }

    return users;
}

QJsonObject Database::getUserById(int id) {
    QSqlQuery query;
    query.prepare("SELECT id, username, role FROM users WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        QJsonObject user;
        user["id"] = query.value("id").toInt();
        user["username"] = query.value("username").toString();
        user["role"] = query.value("role").toString();
        return user;
    }

    return QJsonObject(); // Возвращает пустой объект, если пользователь не найден
}

bool Database::updateUser(int id, const QString &username, const QString &password, const QString &role) {
    QSqlQuery query;
    query.prepare("UPDATE users SET username = :username, password = :password, role = :role WHERE id = :id");
    query.bindValue(":username", username);
    query.bindValue(":password", hashPassword(password)); // Хэшируем пароль перед сохранением
    query.bindValue(":role", role);
    query.bindValue(":id", id);

    return query.exec();
}

bool Database::deleteUser(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = :id");
    query.bindValue(":id", id);

    return query.exec();
}
