#include "basepage.h"

BasePage::BasePage(QWidget *parent) : QWidget(parent) {
    // Создаём основной вертикальный макет
    mainLayout = new QVBoxLayout(this);

    // Панель навигации
    navigationLayout = new QHBoxLayout();
    homeButton = new QPushButton("Главная", this);
    profileButton = new QPushButton("Профиль", this);
    aboutButton = new QPushButton("О нас", this);

    navigationLayout->addWidget(homeButton);
    navigationLayout->addWidget(profileButton);
    navigationLayout->addWidget(aboutButton);

    // Подключаем слоты для кнопок навигации
    connect(homeButton, &QPushButton::clicked, this, &BasePage::onHomeClicked);
    connect(profileButton, &QPushButton::clicked, this, &BasePage::onProfileClicked);
    connect(aboutButton, &QPushButton::clicked, this, &BasePage::onAboutClicked);

    // Добавляем панель навигации в макет
    mainLayout->addLayout(navigationLayout);
}

void BasePage::setCentralWidget(QWidget *widget) {
    if (widget) {
        mainLayout->addWidget(widget);
    }
}

void BasePage::onHomeClicked() {
    emit navigateToPage(0); // Переход на страницу главной
}

void BasePage::onProfileClicked() {
    emit navigateToPage(1); // Переход на страницу профиля
}

void BasePage::onAboutClicked() {
    emit navigateToPage(2); // Переход на страницу "О нас"
}
