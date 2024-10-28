#include "login.h"
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

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);

    loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginButtonClicked);

    setLayout(layout);
}

void Login::onLoginButtonClicked() {
    // Логика авторизации
    if (usernameEdit->text() == "user" && passwordEdit->text() == "pass") { // Пример
        QMessageBox::information(this, "Success", "Login successful!");
        // Здесь можно переключиться на главную страницу
    } else {
        QMessageBox::warning(this, "Error", "Invalid credentials.");
    }
}

