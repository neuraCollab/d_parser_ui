#include "DatabaseManager.h"
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "dotenv.h"  // Подключаем dotenv для загрузки конфигураций

DatabaseManager::DatabaseManager() {
    dotenv::init(".env"); // Загружаем переменные окружения из .env файла

    // Используем переменные из .env файла для настройки базы данных
    QString dbHost = QString::fromStdString(std::getenv("DB_HOST"));
    QString dbName = QString::fromStdString(std::getenv("DB_NAME"));
    QString dbUser = QString::fromStdString(std::getenv("DB_USER"));
    QString dbPassword = QString::fromStdString(std::getenv("DB_PASSWORD"));
    int dbPort = QString::fromStdString(std::getenv("DB_PORT")).toInt();

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(dbHost);
    db.setDatabaseName(dbName);
    db.setUserName(dbUser);
    db.setPassword(dbPassword);
    db.setPort(dbPort);
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
