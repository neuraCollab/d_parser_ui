#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authmanager.h"
#include <QMainWindow>

class QStackedWidget; // Для работы с переключением страниц
class QFrame; // Для карточек прайс-листа

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createHomePage(); // Создание главной страницы
    void createLoginPage(); // Создание страницы входа
    void createRegisterPage(); // Создание страницы регистрации
    void createProfilePage(); // Создание страницы профиля
    void createAboutPage(); // Создание страницы "О нас"
    QFrame *createPricingCard(const QString &title, const QString &description, const QString &buttonText, const QString &color); // Метод для создания карточки прайс-листа

private:
    AuthManager *authManager; // Указатель на менеджер авторизации
    QStackedWidget *stackedWidget; // Для переключения страниц
};

#endif // MAINWINDOW_H
