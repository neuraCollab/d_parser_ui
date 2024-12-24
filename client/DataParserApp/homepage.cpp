#include "homepage.h"
#include "authmanager.h"
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QPixmap>
#include <QMessageBox>
#include <QScreen>
#include <QResizeEvent>

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    // Устанавливаем белый фон
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(Qt::white));
    setPalette(palette);

    mainLayout = new QVBoxLayout(this);

    // Верхняя панель с логотипом и кнопками
    QHBoxLayout *topLayout = new QHBoxLayout;

    QLabel *logoLabel = new QLabel("HWParser", this);
    QFont logoFont("Arial", 16, QFont::Bold);
    logoLabel->setFont(logoFont);

    topLayout->addWidget(logoLabel);

    QPushButton *aboutButton = new QPushButton("О нас", this);
    aboutButton->setStyleSheet("background-color: white; color: black;");
    connect(aboutButton, &QPushButton::clicked, this, &HomePage::onAboutButtonClicked);
    topLayout->addWidget(aboutButton);

    loginButton = new QPushButton("Войти", this);
    loginButton->setStyleSheet("background-color: white; color: black; padding: 5px 15px;");
    registerButton = new QPushButton("Зарегистрироваться", this);
    registerButton->setStyleSheet("background-color: purple; color: white; padding: 5px 15px;");

    connect(loginButton, &QPushButton::clicked, this, &HomePage::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &HomePage::onRegisterButtonClicked);

    topLayout->addStretch();
    topLayout->addWidget(loginButton);
    topLayout->addWidget(registerButton);

    mainLayout->addLayout(topLayout);

    // Hero секция с фоном и кнопкой
    heroImage = new QLabel(this);
    QPixmap pixmap(":/images/hero_bg.jpg");
    heroImage->setPixmap(pixmap);
    heroImage->setScaledContents(true);
    heroImage->setAlignment(Qt::AlignCenter);

    // Контейнер для фона с затемнением
    QVBoxLayout *heroLayout = new QVBoxLayout(heroImage);
    QLabel *overlay = new QLabel(heroImage);
    overlay->setStyleSheet("background-color: rgba(0, 0, 0, 0.5);");
    overlay->setGeometry(0, 0, heroImage->width(), heroImage->height());
    overlay->lower();

    // Краткое описание проекта
    QLabel *descriptionLabel = new QLabel("HWParser - лучший инструмент для анализа и обработки данных.", heroImage);
    descriptionLabel->setStyleSheet(
        "font-size: 28px; font-weight: bold; color: black; text-align: center; padding: 20px;");
    descriptionLabel->setAlignment(Qt::AlignCenter);

    // Кнопка заказа
    QPushButton *orderButton = new QPushButton("Сделать заказ", heroImage);
    orderButton->setStyleSheet(
        "background-color: rgba(255, 255, 255, 0.8);"
        "color: black; font-size: 20px; border-radius: 15px; padding: 10px 20px;");
    orderButton->setFixedSize(200, 50);
    connect(orderButton, &QPushButton::clicked, this, &HomePage::onOrderButtonClicked);

    heroLayout->addStretch();
    heroLayout->addWidget(descriptionLabel, 0, Qt::AlignCenter);
    heroLayout->addWidget(orderButton, 0, Qt::AlignCenter);
    heroLayout->addStretch();

    mainLayout->addWidget(heroImage);

    // Блок с ценами (features) - карточки
    QGridLayout *pricingLayout = new QGridLayout;
    pricingLayout->setSpacing(20);
    pricingLayout->setAlignment(Qt::AlignTop);

    auto createCard = [this](const QString &title, const QString &imagePath, const QString &buttonText) {
        QVBoxLayout *layout = new QVBoxLayout;

        QLabel *titleLabel = new QLabel(title);
        titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: black;");
        titleLabel->setAlignment(Qt::AlignCenter);

        QLabel *imageLabel = new QLabel;
        QPixmap pixmap(imagePath);
        imageLabel->setPixmap(pixmap.scaledToWidth(300, Qt::SmoothTransformation));
        imageLabel->setAlignment(Qt::AlignCenter);

        QPushButton *button = new QPushButton(buttonText);
        button->setStyleSheet("background-color: lightgray; color: black; padding: 10px; border-radius: 5px;");

        connect(button, &QPushButton::clicked, [this, title]() {
            QMessageBox::information(this, "Выбор тарифа", "Вы выбрали тариф: " + title);
        });

        layout->addWidget(titleLabel);
        layout->addWidget(imageLabel);
        layout->addWidget(button, 0, Qt::AlignCenter);

        QWidget *card = new QWidget;
        card->setLayout(layout);
        card->setMinimumHeight(300); // Увеличиваем высоту карточек
        card->setStyleSheet("background-color: #f9fafb; padding: 20px; border-radius: 10px;");
        return card;
    };

    pricingLayout->addWidget(createCard("Бесплатно", ":/images/free_plan.png", "Выбрать"), 0, 0);
    pricingLayout->addWidget(createCard("Стандарт", ":/images/standard_plan.png", "Выбрать"), 0, 1);
    pricingLayout->addWidget(createCard("Премиум", ":/images/premium_plan.png", "Выбрать"), 0, 2);

    mainLayout->addLayout(pricingLayout);

    setLayout(mainLayout);
}

void HomePage::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    int heroImageHeight = 300;
    heroImage->setPixmap(QPixmap(":/images/hero_bg.jpg").scaled(this->width(), heroImageHeight, Qt::KeepAspectRatioByExpanding));
}

void HomePage::onLoginButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget *>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(1);
    }
}

void HomePage::onRegisterButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget *>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(2);
    }
}

void HomePage::onOrderButtonClicked() {
    if (AuthManager::instance().isUserAuthenticated()) {
        QStackedWidget *stackedWidget = qobject_cast<QStackedWidget *>(parent());
        if (stackedWidget) {
            stackedWidget->setCurrentIndex(3);
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Необходимо авторизоваться.");
    }
}

void HomePage::onAboutButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget *>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(4);
    }
}
