#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>

class QPushButton;
class QLabel;

class HomePage : public QWidget {
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();
    void onOrderButtonClicked();

private:
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *orderButton;
    QLabel *aboutLabel;
};

#endif // HOMEPAGE_H
