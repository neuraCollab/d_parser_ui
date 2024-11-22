#include "HttpServer.h"
#include <QHttpServer>
#include <QHttpRequest>
#include <QHttpResponse>
#include <QDebug>

HttpServer::HttpServer(QObject *parent) : QObject(parent) {}

void HttpServer::start() {
    QHttpServer *server = new QHttpServer(this);
    connect(server, &QHttpServer::newRequest, this, &HttpServer::handleParsingRequest);

    if (server->listen(QHostAddress::Any, 8080)) {
        qDebug() << "Сервер запущен на порту 8080";
    } else {
        qDebug() << "Не удалось запустить сервер";
    }
}

void HttpServer::handleParsingRequest(QHttpRequest *req, QHttpResponse *res) {
    QString token = req->header("Authorization").split(" ").last();
    QVariantMap session = sessionManager.getSession(token);
    if (session.isEmpty()) {
        res->writeHead(401);
        res->end("Unauthorized");
        return;
    }

    int userId = session["user_id"].toInt();
    QByteArray fileData = req->body();
    QString fileType = req->header("Content-Type");

    QString tempPath = "/tmp/uploaded_file"; // Временный путь для загрузки файла
    QFile file(tempPath);
    if (!file.open(QIODevice::WriteOnly)) {
        res->writeHead(500);
        res->end("Ошибка при сохранении файла");
        return;
    }
    file.write(fileData);
    file.close();

    if (fileType == "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet") {
        if (fileParser.parseAndStoreLinks(tempPath, userId)) {
            res->writeHead(200);
            res->end("Links processed and stored.");
        } else {
            res->writeHead(500);
            res->end("Error storing links.");
        }
    } else if (fileType == "application/zip") {
        if (fileParser.storeSiteConfig(tempPath, userId)) {
            res->writeHead(200);
            res->end("Config stored.");
        } else {
            res->writeHead(500);
            res->end("Error storing config.");
        }
    } else {
        res->writeHead(400);
        res->end("Unsupported file type.");
    }
}
