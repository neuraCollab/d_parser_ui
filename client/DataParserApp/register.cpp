#include "register.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRegularExpression>

Register::Register(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Ваше имя");
    layout->addWidget(nameEdit);

    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Email");
    layout->addWidget(emailEdit);

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);

    registerButton = new QPushButton("Зарегистрироваться", this);
    registerButton->setStyleSheet("background-color: lightblue; color: darkblue;");
    layout->addWidget(registerButton);

    connect(registerButton, &QPushButton::clicked, this, &Register::onRegisterButtonClicked);

    setLayout(layout);
}

void Register::onRegisterButtonClicked() {
    QString email = emailEdit->text();
    QString password = passwordEdit->text();
    QString name = nameEdit->text();

    // Проверка условий
    if (email.isEmpty() || password.isEmpty() || name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля.");
        return;
    }

    // Проверка email
    QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный email.");
        return;
    }

    // Проверка пароля
    if (password.length() < 4 || !password.contains(QRegularExpression("[0-9]")) || !password.contains(QRegularExpression("[a-zA-Z]"))) {
        QMessageBox::warning(this, "Ошибка", "Пароль должен содержать минимум 4 символа, включая хотя бы одну цифру и букву.");
        return;
    }

    // Здесь должна быть логика добавления пользователя в базу данных

    QMessageBox::information(this, "Успех", "Регистрация прошла успешно!");
}
