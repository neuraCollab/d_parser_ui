#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class Login : public QWidget {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

private slots:
    void onLoginButtonClicked();         // Слот для кнопки "Login"
    void onBackToHomeButtonClicked();    // Слот для кнопки "Назад на главную"

private:
    QLineEdit *usernameEdit;             // Поле ввода имени пользователя
    QLineEdit *passwordEdit;             // Поле ввода пароля
    QPushButton *loginButton;            // Кнопка "Login"
    QPushButton *backToHomeButton;       // Кнопка "Назад на главную"
};

#endif // LOGIN_H
