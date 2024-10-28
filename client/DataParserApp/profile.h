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

private:
    QTextEdit *descriptionEdit;
    QPushButton *submitButton;
};

#endif // PROFILE_H
