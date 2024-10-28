#include "mainwindow.h"
#include "login.h"
#include "mainpage.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPalette>
#include <QPixmap>
#include <QLabel>
#include "homepage.h"
#include "profile.h" // Добавьте это
#include "register.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QStackedWidget *stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    HomePage *homePage = new HomePage(stackedWidget);
    Login *loginPage = new Login(stackedWidget);
    Register *registerPage = new Register(stackedWidget);
    Profile *profilePage = new Profile(stackedWidget);
    MainPage *mainPage = new MainPage(stackedWidget);

    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(registerPage);
    stackedWidget->addWidget(profilePage);
    stackedWidget->addWidget(mainPage);

    setMinimumSize(800, 600);
    setWindowTitle("Data Parser Application");

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(173, 216, 230)); // Светло-голубой
    setPalette(palette);
}
MainWindow::~MainWindow() {}
