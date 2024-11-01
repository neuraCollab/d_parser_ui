#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include "DatabaseManager.h"
#include "SessionManager.h"
#include "FileParser.h"

class HttpServer : public QObject {
    Q_OBJECT
public:
    explicit HttpServer(QObject *parent = nullptr);
    void start();

private slots:
    void handleParsingRequest();

private:
    DatabaseManager dbManager;
    SessionManager sessionManager;
    FileParser fileParser;
};

#endif // HTTPSERVER_H
