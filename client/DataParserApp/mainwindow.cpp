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
    authManager = new AuthManager(this);

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
    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(registerPage);
    stackedWidget->addWidget(profilePage);
    stackedWidget->addWidget(mainPage);

    // Устанавливаем минимальный размер окна и заголовок
    setMinimumSize(800, 600);
    setWindowTitle("Data Parser Application");

    // Настроим палитру
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(255, 255, 255)); // Белый фон
    setPalette(palette);

    // Соединяем сигналы и слоты для обработки входа
    connect(authManager, &AuthManager::loginSuccess, this, [stackedWidget]() {
        QMessageBox::information(nullptr, "Успешный вход", "Авторизация прошла успешно.");
        stackedWidget->setCurrentIndex(3); // Переключаемся на страницу профиля
    });

    connect(authManager, &AuthManager::loginFailed, this, [](const QString &error) {
        QMessageBox::warning(nullptr, "Ошибка входа", error);
    });
}

MainWindow::~MainWindow() {}
