#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class HttpServer : public QObject {
    Q_OBJECT
public:
    explicit HttpServer(QObject *parent = nullptr);
    void start();

private slots:
    void handleNewConnection();
    void handleReadyRead();

private:
    QTcpServer *server;
};

#endif // HTTPSERVER_H
