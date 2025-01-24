#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QHttpServer>
#include <QHttpServerRouter>
#include <QHttpServerRequest>
#include <QHttpServerResponse>
#include <QJsonObject>
#include "database.h"
#include <QString>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);

private:
    QHttpServer *server;                  // HTTP server instance
    QHttpServerRouter *router;           // Router for managing routes
    Database *db;                         // Pointer to the database instance
    QString secretKey = "YOUR_SECRET_KEY"; // Replace with your actual secret key

    // Route handlers
    QHttpServerResponse handleUpload(const QHttpServerRequest &request);
    QHttpServerResponse handleFileRetrieval(int id);
    QHttpServerResponse handleFileDeletion(int id);
    QHttpServerResponse handleProtectedRoute(const QHttpServerRequest &request);

    // CRUD route handlers for users
    QHttpServerResponse handleCreateUser(const QHttpServerRequest &request);
    QHttpServerResponse handleGetAllUsers(const QHttpServerRequest &request);
    QHttpServerResponse handleGetUserById(int id, const QHttpServerRequest &request);
    QHttpServerResponse handleUpdateUser(int id, const QHttpServerRequest &request);
    QHttpServerResponse handleDeleteUser(int id, const QHttpServerRequest &request);

    // Token management
    QString createToken(const QJsonObject &data);
    bool validateToken(const QString &token, QJsonObject &payload);
};

#endif // SERVER_H
