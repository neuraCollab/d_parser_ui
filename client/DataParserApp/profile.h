#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QTextEdit;

class Profile : public QWidget {
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);

private slots:
    void onSubmitButtonClicked();
    void onBackToHomeButtonClicked();

private:
    QTextEdit *descriptionEdit;
    QPushButton *submitButton;
    QPushButton *backToHomeButton;
};

#endif // PROFILE_H
