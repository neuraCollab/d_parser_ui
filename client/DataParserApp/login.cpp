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
    usernameEdit->setStyleSheet("background-color: white; color: black;"); // Устанавливаем стиль поля ввода
    layout->addWidget(usernameEdit);

    // Поле ввода пароля
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet("background-color: white; color: black;"); // Устанавливаем стиль поля ввода
    layout->addWidget(passwordEdit);

    // Кнопка входа
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    loginButton = new QPushButton("Login", this);
    loginButton->setStyleSheet("background-color: lightblue; color: darkblue;");
    loginButton->setFixedSize(100, 30);
    buttonLayout->addStretch();         // Отступ слева
    buttonLayout->addWidget(loginButton, 0, Qt::AlignCenter); // Центрируем кнопку
    buttonLayout->addStretch();         // Отступ справа
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
