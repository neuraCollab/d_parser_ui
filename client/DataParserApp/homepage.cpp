#include "homepage.h"
#include "qstackedwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QPalette>

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;

    // Стиль фона
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(173, 216, 230)); // Светло-голубой
    setPalette(palette);

    // Текст о нас
    aboutLabel = new QLabel("Аня, Миша, Даня и Олег, вот они - выжившие группы 17", this);
    aboutLabel->setAlignment(Qt::AlignCenter);
    aboutLabel->setStyleSheet("font-weight: bold; color: darkblue; font-size: 16px;");
    layout->addWidget(aboutLabel);

    // Кнопка входа
    loginButton = new QPushButton("Войти", this);
    loginButton->setStyleSheet("background-color: lightblue; color: darkblue;");
    connect(loginButton, &QPushButton::clicked, this, &HomePage::onLoginButtonClicked);
    layout->addWidget(loginButton);

    // Кнопка регистрации
    registerButton = new QPushButton("Зарегистрироваться", this);
    registerButton->setStyleSheet("background-color: lightblue; color: darkblue;");
    connect(registerButton, &QPushButton::clicked, this, &HomePage::onRegisterButtonClicked);
    layout->addWidget(registerButton);

    // Кнопка "Сделать заказ"
    orderButton = new QPushButton("Сделать заказ", this);
    orderButton->setStyleSheet("background-color: lightblue; color: darkblue;");
    connect(orderButton, &QPushButton::clicked, this, &HomePage::onOrderButtonClicked);
    layout->addWidget(orderButton);

    // Фоновое изображение
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap("C:/Users/annap/Downloads/Telegram Desktop/photo_2024-10-28_20-53-09.jpg");
    imageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
    imageLabel->setStyleSheet("border: 1px solid black;"); // Рамка для изображения
    layout->addWidget(imageLabel);

    setLayout(layout);
}

void HomePage::onLoginButtonClicked() {
    // Логика перехода на страницу авторизации
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(1); // Индекс страницы входа
    }
}

void HomePage::onRegisterButtonClicked() {
    // Логика перехода на страницу регистрации
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(2); // Индекс страницы регистрации
    }
}

void HomePage::onOrderButtonClicked() {
    // Логика перехода в личный кабинет
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(3); // Индекс личного кабинета
    }
}

