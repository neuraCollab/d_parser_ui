#include "login.h"
#include "qstackedwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

Login::Login(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;

    // Поле ввода имени пользователя
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Username");
    layout->addWidget(usernameEdit);

    // Поле ввода пароля
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);

    // Кнопка входа
    loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginButtonClicked);

    setLayout(layout);
}

void Login::onLoginButtonClicked() {
    if (usernameEdit->text() == "user" && passwordEdit->text() == "pass") {
        QMessageBox::information(this, "Success", "Login successful!");
        QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
        if (stackedWidget) {
            stackedWidget->setCurrentIndex(4); // Индекс главной страницы
        }
    } else {
        QMessageBox::warning(this, "Error", "Invalid credentials.");
    }
}

