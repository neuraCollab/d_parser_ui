#ifndef ABOUTPAGE_H
#define ABOUTPAGE_H

#include <QWidget>

class QPushButton;

class AboutPage : public QWidget {
    Q_OBJECT

public:
    explicit AboutPage(QWidget *parent = nullptr);

private slots:
    void onBackToHomeButtonClicked(); // Слот для кнопки возврата на главную страницу

private:
    QPushButton *backToHomeButton; // Кнопка для возврата
};

#endif // ABOUTPAGE_H
