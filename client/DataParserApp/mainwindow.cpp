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

    setMinimumSize(800, 600);
    setWindowTitle("Data Parser Application");

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(255, 182, 193)); // Светло-розовый цвет
    setPalette(palette);

    QLabel *background = new QLabel(this);
    QPixmap pixmap(":/heart.png"); // Загружает изображение heart.png
    background->setPixmap(pixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    background->setScaledContents(true);
    background->lower(); // Помещаем изображение на задний план
}

MainWindow::~MainWindow() {}
