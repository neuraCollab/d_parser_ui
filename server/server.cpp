#include "server.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QDateTime>
#include <QTcpServer>

Server::Server(QObject *parent) : QObject(parent), server(new QHttpServer(this)) {
    // Route for root path
    server->route("/", []() {
        return QHttpServerResponse(QByteArray("Hello, world!"), QHttpServerResponse::StatusCode::Ok);
    });

    // Route for uploading files
    server->route("/upload", [this](const QHttpServerRequest &request) {
        if (request.method() != QHttpServerRequest::Method::Post) {
            return QHttpServerResponse(QByteArray("Only POST method allowed"), QHttpServerResponse::StatusCode::MethodNotAllowed);
        }

        QString filePath = QString("uploads/uploaded_file_%1.txt").arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss_zzz"));
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(request.body());
            file.close();
            return QHttpServerResponse(QByteArray("File uploaded successfully"), QHttpServerResponse::StatusCode::Ok);
        }

        return QHttpServerResponse(QByteArray("Failed to save file"), QHttpServerResponse::StatusCode::InternalServerError);
    });

    // Route for retrieving files
    server->route("/files/<int>", [this](int id) {
        QString filePath = "uploads/" + QString::number(id);
        QFile file(filePath);
        if (file.exists() && file.open(QIODevice::ReadOnly)) {
            return QHttpServerResponse(QByteArray("application/octet-stream"), file.readAll(), QHttpServerResponse::StatusCode::Ok);
        }
        return QHttpServerResponse(QByteArray("File not found"), QHttpServerResponse::StatusCode::NotFound);
    });

    // Route for user registration
    server->route("/register", [this](const QHttpServerRequest &request) {
        QJsonDocument doc = QJsonDocument::fromJson(request.body());
        QJsonObject obj = doc.object();

        QString username = obj["username"].toString();
        QString password = obj["password"].toString();
        QString role = obj["role"].toString();

        if (username.isEmpty() || password.isEmpty() || role.isEmpty()) {
            return QHttpServerResponse(QByteArray("Invalid input"), QHttpServerResponse::StatusCode::BadRequest);
        }

        // Hash password
        QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

        if (db->addUser(username, hashedPassword, role)) {
            return QHttpServerResponse(QByteArray("User registered successfully"), QHttpServerResponse::StatusCode::Ok);
        }
        return QHttpServerResponse(QByteArray("Failed to register user"), QHttpServerResponse::StatusCode::InternalServerError);
    });

    // Route for user login
    server->route("/login", [this](const QHttpServerRequest &request) {
        QJsonDocument doc = QJsonDocument::fromJson(request.body());
        QJsonObject obj = doc.object();

        QString username = obj["username"].toString();
        QString password = obj["password"].toString();

        if (username.isEmpty() || password.isEmpty()) {
            return QHttpServerResponse(QByteArray("Invalid input"), QHttpServerResponse::StatusCode::BadRequest);
        }

        // Hash password
        QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

        QString role = db->getUserRole(username, hashedPassword);
        if (!role.isEmpty()) {
            QJsonObject payload;
            payload["username"] = username;
            payload["role"] = role;
            payload["exp"] = QDateTime::currentSecsSinceEpoch() + 3600; // Token valid for 1 hour
            QString token = createToken(payload);

            QJsonObject response;
            response["token"] = token;
            response["role"] = role;
            // qDebug() << "Generated token:" << token;
            qDebug() << "Response JSON:" << QJsonDocument(response).toJson();

            return QHttpServerResponse(QJsonDocument(response).toJson(), QHttpServerResponse::StatusCode::Ok);
        }

        return QHttpServerResponse(QByteArray("Invalid username or password"), QHttpServerResponse::StatusCode::Unauthorized);
    });

    server->route("/protected", [this](const QHttpServerRequest &request) {
        QString authHeader = QString::fromUtf8(request.headers().value("Authorization"));

        if (authHeader.isEmpty() || !authHeader.startsWith("Bearer ")) {
            return QHttpServerResponse(QByteArray("Missing or invalid Authorization header"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        QString token = authHeader.mid(7); // Remove "Bearer "
        QJsonObject payload;

        if (!validateToken(token, payload)) {
            return QHttpServerResponse(QByteArray("Invalid or expired token"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        return QHttpServerResponse(QJsonDocument(payload).toJson(), QHttpServerResponse::StatusCode::Ok);
    });

    // Route for creating a new user (only admin can create users)
    server->route("/users", [this](const QHttpServerRequest &request) {
        QString authHeader = QString::fromUtf8(request.headers().value("Authorization"));
        if (authHeader.isEmpty() || !authHeader.startsWith("Bearer ")) {
            return QHttpServerResponse(QByteArray("Missing or invalid Authorization header"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        QString token = authHeader.mid(7); // Remove "Bearer "
        QJsonObject payload;
        if (!validateToken(token, payload)) {
            return QHttpServerResponse(QByteArray("Invalid or expired token"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        if (payload["role"].toString() != "admin") {
            return QHttpServerResponse(QByteArray("Forbidden"), QHttpServerResponse::StatusCode::Forbidden);
        }

        QJsonDocument doc = QJsonDocument::fromJson(request.body());
        QJsonObject obj = doc.object();

        QString username = obj["username"].toString();
        QString password = obj["password"].toString();
        QString role = obj["role"].toString();

        if (username.isEmpty() || password.isEmpty() || role.isEmpty()) {
            return QHttpServerResponse(QByteArray("Invalid input"), QHttpServerResponse::StatusCode::BadRequest);
        }

        QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
        if (db->addUser(username, hashedPassword, role)) {
            return QHttpServerResponse(QByteArray("User created successfully"), QHttpServerResponse::StatusCode::Ok);
        }
        return QHttpServerResponse(QByteArray("Failed to create user"), QHttpServerResponse::StatusCode::InternalServerError);
    });

    // Route for retrieving all users (only admin can retrieve all users)
    server->route("/users", [this](const QHttpServerRequest &request) {
        QString authHeader = QString::fromUtf8(request.headers().value("Authorization"));
        if (authHeader.isEmpty() || !authHeader.startsWith("Bearer ")) {
            return QHttpServerResponse(QByteArray("Missing or invalid Authorization header"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        QString token = authHeader.mid(7); // Remove "Bearer "
        QJsonObject payload;
        if (!validateToken(token, payload)) {
            return QHttpServerResponse(QByteArray("Invalid or expired token"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        if (payload["role"].toString() != "admin") {
            return QHttpServerResponse(QByteArray("Forbidden"), QHttpServerResponse::StatusCode::Forbidden);
        }

        QJsonArray users = db->getAllUsers();
        return QHttpServerResponse(QJsonDocument(users).toJson(), QHttpServerResponse::StatusCode::Ok);
    });

    // Route for retrieving a single user (admin and user can access their own data)
    server->route("/users/<int>", [this](int id, const QHttpServerRequest &request) {
        QString authHeader = QString::fromUtf8(request.headers().value("Authorization"));
        if (authHeader.isEmpty() || !authHeader.startsWith("Bearer ")) {
            return QHttpServerResponse(QByteArray("Missing or invalid Authorization header"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        QString token = authHeader.mid(7); // Remove "Bearer "
        QJsonObject payload;
        if (!validateToken(token, payload)) {
            return QHttpServerResponse(QByteArray("Invalid or expired token"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        QString role = payload["role"].toString();
        QString username = payload["username"].toString();

        QJsonObject user = db->getUserById(id);
        if (role == "admin" || (role == "user" && user["username"].toString() == username)) {
            return QHttpServerResponse(QJsonDocument(user).toJson(), QHttpServerResponse::StatusCode::Ok);
        }

        return QHttpServerResponse(QByteArray("Forbidden"), QHttpServerResponse::StatusCode::Forbidden);
    });

    // Route for updating a user (only admin can update users)
    server->route("/users/<int>", [this](int id, const QHttpServerRequest &request) {
        QString authHeader = QString::fromUtf8(request.headers().value("Authorization"));
        if (authHeader.isEmpty() || !authHeader.startsWith("Bearer ")) {
            return QHttpServerResponse(QByteArray("Missing or invalid Authorization header"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        QString token = authHeader.mid(7); // Remove "Bearer "
        QJsonObject payload;
        if (!validateToken(token, payload)) {
            return QHttpServerResponse(QByteArray("Invalid or expired token"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        if (payload["role"].toString() != "admin") {
            return QHttpServerResponse(QByteArray("Forbidden"), QHttpServerResponse::StatusCode::Forbidden);
        }

        QJsonDocument doc = QJsonDocument::fromJson(request.body());
        QJsonObject obj = doc.object();

        QString username = obj["username"].toString();
        QString password = obj["password"].toString();
        QString role = obj["role"].toString();

        if (db->updateUser(id, username, password, role)) {
            return QHttpServerResponse(QByteArray("User updated successfully"), QHttpServerResponse::StatusCode::Ok);
        }
        return QHttpServerResponse(QByteArray("Failed to update user"), QHttpServerResponse::StatusCode::InternalServerError);
    });

    // Route for deleting a user (only admin can delete users)
    server->route("/users/<int>", [this](int id, const QHttpServerRequest &request) {
        QString authHeader = QString::fromUtf8(request.headers().value("Authorization"));
        if (authHeader.isEmpty() || !authHeader.startsWith("Bearer ")) {
            return QHttpServerResponse(QByteArray("Missing or invalid Authorization header"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        QString token = authHeader.mid(7); // Remove "Bearer "
        QJsonObject payload;
        if (!validateToken(token, payload)) {
            return QHttpServerResponse(QByteArray("Invalid or expired token"), QHttpServerResponse::StatusCode::Unauthorized);
        }

        if (payload["role"].toString() != "admin") {
            return QHttpServerResponse(QByteArray("Forbidden"), QHttpServerResponse::StatusCode::Forbidden);
        }

        if (db->deleteUser(id)) {
            return QHttpServerResponse(QByteArray("User deleted successfully"), QHttpServerResponse::StatusCode::Ok);
        }
        return QHttpServerResponse(QByteArray("Failed to delete user"), QHttpServerResponse::StatusCode::InternalServerError);
    });






    // Start listening on the server
    auto tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, 8080) || !server->bind(tcpServer)) {
        qCritical() << "Failed to start the server!";
        delete tcpServer;
        return;
    }

    qDebug() << "Server is running on port" << tcpServer->serverPort();
}

QString Server::createToken(const QJsonObject &data) {
    QByteArray payload = QJsonDocument(data).toJson(QJsonDocument::Compact);
    QByteArray signature = QCryptographicHash::hash(secretKey.toUtf8() + payload, QCryptographicHash::Sha256);

    return QString(payload.toBase64() + "." + signature.toBase64());
}

bool Server::validateToken(const QString &token, QJsonObject &payload) {
    QStringList parts = token.split('.');
    if (parts.size() != 2) {
        qWarning() << "Invalid token format";
        return false;
    }

    QByteArray decodedPayload = QByteArray::fromBase64(parts[0].toUtf8());
    QByteArray receivedSignature = QByteArray::fromBase64(parts[1].toUtf8());
    QByteArray computedSignature = QCryptographicHash::hash(secretKey.toUtf8() + decodedPayload, QCryptographicHash::Sha256);

    if (receivedSignature != computedSignature) {
        qWarning() << "Invalid token signature";
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(decodedPayload);
    if (!doc.isObject()) {
        qWarning() << "Invalid token payload";
        return false;
    }

    payload = doc.object();

    qint64 exp = payload["exp"].toVariant().toLongLong();
    if (QDateTime::currentSecsSinceEpoch() > exp) {
        qWarning() << "Token expired";
        return false;
    }

    return true;
}
