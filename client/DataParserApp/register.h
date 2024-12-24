#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class QLineEdit;
class QPushButton;

class Register : public QWidget {
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);

private slots:
    void onRegisterButtonClicked(); // Слот для обработки нажатия кнопки "Зарегистрироваться"
    void onBackToHomeButtonClicked(); // Слот для обработки нажатия кнопки "Назад на главную"
    void onRegisterFinished(QNetworkReply *reply); // Слот для обработки ответа сервера

private:
    QLineEdit *nameEdit; // Поле ввода имени
    QLineEdit *emailEdit; // Поле ввода email
    QLineEdit *passwordEdit; // Поле ввода пароля
    QPushButton *registerButton; // Кнопка "Зарегистрироваться"
    QPushButton *backToHomeButton; // Кнопка "Назад на главную"

    QNetworkAccessManager *networkManager; // Объект для выполнения сетевых запросов

    void sendRegisterRequest(const QString &name, const QString &email, const QString &password); // Метод для отправки регистрационного запроса
};

#endif // REGISTER_H
