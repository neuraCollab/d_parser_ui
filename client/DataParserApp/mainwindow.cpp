#include "mainwindow.h"
#include "login.h"
#include "mainpage.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPalette>
#include <QPixmap>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    Login *loginPage = new Login(stackedWidget);
    MainPage *mainPage = new MainPage(stackedWidget);

    stackedWidget->addWidget(loginPage);
    stackedWidget->addWidget(mainPage);

}
