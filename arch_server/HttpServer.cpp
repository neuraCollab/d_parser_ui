#include "HttpServer.h"
#include <QHostAddress>
#include <QDebug>

HttpServer::HttpServer(QObject *parent) : QObject(parent), server(new QTcpServer(this)) {
    connect(server, &QTcpServer::newConnection, this, &HttpServer::handleNewConnection);
}

void HttpServer::start() {
    if (server->listen(QHostAddress::Any, 8080)) {
        qDebug() << "Сервер запущен на порту 8080";
    } else {
        qDebug() << "Не удалось запустить сервер";
    }
}

void HttpServer::handleNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &HttpServer::handleReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

void HttpServer::handleReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QByteArray requestData = clientSocket->readAll();
    QString request(requestData);

    // Пример обработки GET-запроса
    if (request.startsWith("GET")) {
        QString response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
        clientSocket->write(response.toUtf8());
        clientSocket->disconnectFromHost();
    }
    // Пример обработки POST-запроса
    else if (request.startsWith("POST")) {
        // Извлечение данных из запроса
        int contentIndex = request.indexOf("\r\n\r\n");
        if (contentIndex != -1) {
            QByteArray postData = requestData.mid(contentIndex + 4);
            // Обработка postData
            QString response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nData received.";
            clientSocket->write(response.toUtf8());
            clientSocket->disconnectFromHost();
        }
    }
    // Обработка других типов запросов
    else {
        QString response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nUnsupported request.";
        clientSocket->write(response.toUtf8());
        clientSocket->disconnectFromHost();
    }
}
