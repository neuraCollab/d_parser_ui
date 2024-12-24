#include "mainwindow.h"
#include "login.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPalette>
#include <QPixmap>
#include <QLabel>
#include "homepage.h"
#include "profile.h"
#include "register.h"
#include "aboutpage.h"
#include "authmanager.h"

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
}

MainWindow::~MainWindow() {}
