#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "authmanager.h"
#include <QNetworkAccessManager>

class QLineEdit;
class QPushButton;
class QNetworkReply;

class Login : public QWidget {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    void setAuthManager(AuthManager *authManager);

private slots:
    void onLoginButtonClicked();         // Слот для кнопки "Login"
    void onBackToHomeButtonClicked();    // Слот для кнопки "Назад на главную"
    void onLoginFinished(QNetworkReply *reply);  // Слот для обработки ответа на запрос

private:
    AuthManager *authManager;
    QLineEdit *usernameEdit;             // Поле ввода имени пользователя
    QLineEdit *passwordEdit;             // Поле ввода пароля
    QPushButton *loginButton;            // Кнопка "Login"
    QPushButton *backToHomeButton;       // Кнопка "Назад на главную"
    QNetworkAccessManager *networkManager; // Менеджер для сетевых запросов

    void sendLoginRequest(const QString &username, const QString &password);  // Декларация метода
};

#endif // LOGIN_H
