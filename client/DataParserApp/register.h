#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class Register : public QWidget {
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);

private slots:
    void onRegisterButtonClicked();
    void onBackToHomeButtonClicked();

private:
    QLineEdit *nameEdit;
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QPushButton *registerButton;
    QPushButton *backToHomeButton;
};

#endif // REGISTER_H
