#include "homepage.h"
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QGradient>
#include <QLinearGradient>

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    // Устанавливаем белый фон
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(Qt::white));
    setPalette(palette);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Верхняя панель с логотипом и кнопками
    QHBoxLayout *topLayout = new QHBoxLayout;

    // Логотип "HWParser" с необычным стилем
    QLabel *logoLabel = new QLabel("HWParser", this);
    QFont logoFont("Arial", 16, QFont::Bold); // Настройка шрифта
    logoLabel->setFont(logoFont);

    // Градиент для текста логотипа
    QPalette logoPalette;
    QLinearGradient gradient(0, 0, 100, 0);
    gradient.setColorAt(0, QColor(128, 0, 128));  // Фиолетовый
    gradient.setColorAt(1, QColor(186, 85, 211)); // Светло-фиолетовый
    logoPalette.setBrush(QPalette::WindowText, gradient);
    logoLabel->setPalette(logoPalette);

    topLayout->addWidget(logoLabel);

    // Кнопка "О нас"
    QPushButton *aboutButton = new QPushButton("О нас", this);
    aboutButton->setStyleSheet("background-color: white; color: black;");
    connect(aboutButton, &QPushButton::clicked, this, &HomePage::onAboutButtonClicked);
    topLayout->addWidget(aboutButton);

    // Добавление кнопок Войти и Зарегистрироваться в верхний правый угол
    loginButton = new QPushButton("Войти", this);
    loginButton->setStyleSheet("background-color: white; color: black;");
    registerButton = new QPushButton("Зарегистрироваться", this);
    registerButton->setStyleSheet("background-color: purple; color: white;");

    connect(loginButton, &QPushButton::clicked, this, &HomePage::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &HomePage::onRegisterButtonClicked);

    topLayout->addStretch();
    topLayout->addWidget(loginButton);
    topLayout->addWidget(registerButton);

    mainLayout->addLayout(topLayout);

    // Кнопка "Сделать заказ" в центре
    orderButton = new QPushButton("Сделать заказ", this);
    orderButton->setStyleSheet("background-color: purple; color: white;");
    connect(orderButton, &QPushButton::clicked, this, &HomePage::onOrderButtonClicked);

    mainLayout->addStretch();
    mainLayout->addWidget(orderButton, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void HomePage::onLoginButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(1); // Индекс страницы входа
    }
}

void HomePage::onRegisterButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(2); // Индекс страницы регистрации
    }
}

void HomePage::onOrderButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(3); // Индекс страницы личного кабинета
    }
}

void HomePage::onAboutButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(4); // Индекс страницы "О нас"
    }
}
