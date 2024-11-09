#include "login.h"
#include "qstackedwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

Login::Login(QWidget *parent) : QWidget(parent) {
    // Основная компоновка страницы
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Горизонтальная компоновка для размещения кнопки слева
    QHBoxLayout *topLayout = new QHBoxLayout;

    // Создаем кнопку "Назад на главную"
    QPushButton *backToHomeButton = new QPushButton("Назад на главную", this);
    backToHomeButton->setStyleSheet("background-color: white; color: black;"); // Устанавливаем стиль кнопки

    // Подключаем слот для обработки нажатия
    connect(backToHomeButton, &QPushButton::clicked, this, &Login::onBackToHomeButtonClicked);

    // Добавляем кнопку в левую часть горизонтальной компоновки
    topLayout->addWidget(backToHomeButton, 0, Qt::AlignLeft);

    // Добавляем отступ в правую часть горизонтальной компоновки, чтобы кнопка оставалась слева
    topLayout->addStretch();

    // Добавляем горизонтальную компоновку в основную вертикальную
    layout->addLayout(topLayout);

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

    // Подключаем сигнал для кнопки входа
    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginButtonClicked);

    setLayout(layout);
}

void Login::onLoginButtonClicked() {
    if (usernameEdit->text() == "user" && passwordEdit->text() == "pass") {
        QMessageBox::information(this, "Success", "Login successful!");
        QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
        if (stackedWidget) {
            stackedWidget->setCurrentIndex(4); // Индекс страницы после успешного входа
        }
    } else {
        QMessageBox::warning(this, "Error", "Invalid credentials.");
    }
}

// Слот для кнопки возврата на главную страницу
void Login::onBackToHomeButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0); // Переключаемся на главную страницу
    }
}
