#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authmanager.h"
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void createHomePage();
private:
    void createLoginPage();
private:
    AuthManager *authManager;
};


#endif // MAINWINDOW_H
