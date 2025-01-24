#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QVariantMap>

class DatabaseManager {
public:
    DatabaseManager();
    bool open();
    void close();
    bool addUser(const QString& username, const QString& passwordHash, const QString& email, const QString& clientKey);
    QVariantMap getUser(const QString& username);
    bool updateUserPassword(int userId, const QString& newPasswordHash);
    bool deleteUser(int userId);

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
