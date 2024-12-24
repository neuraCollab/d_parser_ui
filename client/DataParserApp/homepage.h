#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "authmanager.h"

class QPushButton;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class HomePage : public QWidget {
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override; // Обрабатываем изменение размера окна

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();
    void onOrderButtonClicked();
    void onAboutButtonClicked(); // Слот для кнопки "О нас"

private:
    AuthManager *authManager;

    // Элементы интерфейса
    QVBoxLayout *mainLayout;   // Основной макет
    QLabel *heroImage;         // Лейбл для изображения Hero
    QHBoxLayout *pricingLayout; // Макет для отображения планов

    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *orderButton;
};

#endif // HOMEPAGE_H
