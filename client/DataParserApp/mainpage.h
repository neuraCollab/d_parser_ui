#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

class QPushButton;
class QLineEdit;

class MainPage : public QWidget {
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);

private slots:
    void onUploadButtonClicked();

private:
    QLineEdit *fileLineEdit;
    QPushButton *uploadButton;
};

#endif // MAINPAGE_H
