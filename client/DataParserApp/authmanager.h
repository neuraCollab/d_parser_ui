#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class AuthManager : public QObject {
    Q_OBJECT

public:
    explicit AuthManager(QObject *parent = nullptr);

    void login(const QString &username, const QString &password);

    static void saveToken(const QString &token);
    static QString loadToken();
    static bool isUserAuthenticated();
    static void clearToken();

    QString getToken() const;  // Объявление метода как const

signals:
    void loginSuccess();     // Сигнал успешного логина
    void loginFailed(const QString &error); // Сигнал неудачного логина

private slots:
    void onLoginReply();  // Слот для обработки ответа на запрос авторизации

private:
    void setToken(const QString &token);

    QString jwtToken;  // Токен
    bool isAuthenticated;  // Статус авторизации
    QNetworkAccessManager *networkManager;  // Менеджер для сетевых запросов
};

#endif // AUTHMANAGER_H
