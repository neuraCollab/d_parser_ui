#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "homepage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void createHomePage();
private:
    void createLoginPage();
    void createMainPage();
};


#endif // MAINWINDOW_H
