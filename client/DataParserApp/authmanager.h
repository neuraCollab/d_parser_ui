#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QString>

class AuthManager : public QObject {
    Q_OBJECT

public:
    // Singleton: метод для доступа к единственному экземпляру класса
    static AuthManager &instance();

    // Удаляем копирование и перемещение, чтобы гарантировать уникальность экземпляра
    AuthManager(const AuthManager &) = delete;
    AuthManager &operator=(const AuthManager &) = delete;

    // Методы авторизации
    void login(const QString &username, const QString &password);
    void logout();
    QString getToken() const;
    static void saveToken(const QString &token);
    static QString loadToken();
    bool isUserAuthenticated() const;

signals:
    void loginSuccess(const QString &role); // Передаём роль пользователя
    void loginFailed(const QString &error);
    void loggedOut();

private:
    // Приватный конструктор для реализации Singleton
    explicit AuthManager(QObject *parent = nullptr);

    // Методы для работы с токенами
    void setToken(const QString &token);
    void clearToken();

    // Поля для хранения данных
    QString jwtToken;                        // Хранит токен авторизации
    bool isAuthenticated;                    // Флаг авторизации
    QNetworkAccessManager *networkManager;   // Для выполнения сетевых запросов

private slots:
    void onLoginReply();
};

#endif // AUTHMANAGER_H
