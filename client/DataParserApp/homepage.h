#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "authmanager.h"

class QPushButton;
class QLabel;

class HomePage : public QWidget {
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();
    void onOrderButtonClicked();
    void onAboutButtonClicked(); // Слот для кнопки "О нас"

private:
    AuthManager *authManager;

    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *orderButton;
};

#endif // HOMEPAGE_H
