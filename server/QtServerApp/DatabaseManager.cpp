#include "DatabaseManager.h"
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <libenvpp/env.hpp> // Подключаем libenvpp для работы с переменными окружения

DatabaseManager::DatabaseManager() {
    // Устанавливаем префикс для переменных окружения
    auto pre = env::prefix("DB");

    // Регистрируем необходимые переменные окружения
    const auto host_id = pre.register_required_variable<std::string>("HOST");
    const auto name_id = pre.register_required_variable<std::string>("NAME");
    const auto user_id = pre.register_required_variable<std::string>("USER");
    const auto password_id = pre.register_required_variable<std::string>("PASSWORD");
    const auto port_id = pre.register_required_variable<int>("PORT");

    // Парсим и валидируем зарегистрированные переменные
    const auto parsed_env = pre.parse_and_validate();

    if (!parsed_env.ok()) {
        qDebug() << "Ошибка при загрузке переменных окружения:";
        qDebug() << QString::fromStdString(parsed_env.error_message());
        return;
    }

    // Получаем значения переменных
    QString dbHost = QString::fromStdString(parsed_env.get(host_id));
    QString dbName = QString::fromStdString(parsed_env.get(name_id));
    QString dbUser = QString::fromStdString(parsed_env.get(user_id));
    QString dbPassword = QString::fromStdString(parsed_env.get(password_id));
    int dbPort = parsed_env.get(port_id);

    // Настраиваем подключение к базе данных
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
