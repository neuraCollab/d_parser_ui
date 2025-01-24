#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonArray>
#include <QJsonObject>
#include <QCryptographicHash>

class Database : public QObject {
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);

    // Пользовательские операции
    bool addUser(const QString &username, const QString &password, const QString &role); // Добавление пользователя
    QString getUserRole(const QString &username, const QString &password);              // Получение роли пользователя
    QJsonArray getAllUsers();                                                           // Получение всех пользователей
    QJsonObject getUserById(int id);                                                    // Получение пользователя по ID
    bool updateUser(int id, const QString &username, const QString &password, const QString &role); // Обновление пользователя
    bool deleteUser(int id);                                                            // Удаление пользователя

private:
    QSqlDatabase db;
    void initializeDatabase(); // Инициализация базы данных
    QString hashPassword(const QString &password); // Хэширование пароля
};

#endif // DATABASE_H
