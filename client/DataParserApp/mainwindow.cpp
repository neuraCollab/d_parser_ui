#include "mainwindow.h"
#include "login.h"
#include "homepage.h"
#include "profile.h"
#include "register.h"
#include "aboutpage.h"
#include "authmanager.h"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QPalette>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Получаем Singleton экземпляр AuthManager
    AuthManager &authManager = AuthManager::instance();

    // Создание QStackedWidget
    QStackedWidget *stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Создание страниц
    HomePage *homePage = new HomePage(stackedWidget);
    Login *loginPage = new Login(stackedWidget);
    Register *registerPage = new Register(stackedWidget);
    Profile *profilePage = new Profile(stackedWidget);
    AboutPage *mainPage = new AboutPage(stackedWidget);

    // Добавляем страницы в QStackedWidget
    stackedWidget->addWidget(homePage);      // Индекс 0
    stackedWidget->addWidget(loginPage);     // Индекс 1
    stackedWidget->addWidget(registerPage);  // Индекс 2
    stackedWidget->addWidget(profilePage);   // Индекс 3
    stackedWidget->addWidget(mainPage);      // Индекс 4

    // Устанавливаем минимальный размер окна и заголовок
    setMinimumSize(800, 600);
    setWindowTitle("Data Parser Application");

    // Настраиваем палитру
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(255, 255, 255)); // Белый фон
    setPalette(palette);

    // Футер для всех страниц
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *footerLayout = new QHBoxLayout;

    QLabel *footerLabel = new QLabel("© 2024 Data Parser Application. Все права защищены.", this);
    footerLabel->setStyleSheet("color: gray; font-size: 12px;");

    QPushButton *contactButton = new QPushButton("Связаться с нами", this);
    contactButton->setStyleSheet("background-color: white; color: black; border: 1px solid gray; font-size: 12px;");

    connect(contactButton, &QPushButton::clicked, this, []() {
        QMessageBox::information(nullptr, "Контакты", "Почта: support@dataparser.com\nТелефон: +7 (999) 123-45-67");
    });

    footerLayout->addStretch();
    footerLayout->addWidget(footerLabel);
    footerLayout->addWidget(contactButton);
    footerLayout->addStretch();

    mainLayout->addWidget(stackedWidget);
    mainLayout->addLayout(footerLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Соединяем сигналы и слоты для обработки входа
    connect(&authManager, &AuthManager::loginSuccess, this, [stackedWidget](const QString &role) {
        QMessageBox::information(nullptr, "Успешный вход", "Авторизация прошла успешно. Роль: " + role);
        stackedWidget->setCurrentIndex(3); // Переключаемся на страницу профиля
    });

    connect(&authManager, &AuthManager::loginFailed, this, [](const QString &error) {
        QMessageBox::warning(nullptr, "Ошибка входа", error);
    });

    connect(&authManager, &AuthManager::loggedOut, this, [stackedWidget]() {
        QMessageBox::information(nullptr, "Выход", "Вы успешно вышли из системы.");
        stackedWidget->setCurrentIndex(0); // Возврат на главную страницу
    });

    // Устанавливаем окно на весь экран
    showMaximized();
}

MainWindow::~MainWindow() {}
