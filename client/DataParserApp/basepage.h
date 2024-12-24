#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>

class BasePage : public QWidget {
    Q_OBJECT

public:
    explicit BasePage(QWidget *parent = nullptr);
    virtual ~BasePage() = default;

    void setCentralWidget(QWidget *widget); // Устанавливаем центральное содержимое

signals:
    void navigateToPage(int index); // Сигнал для перехода между страницами

protected:
    QVBoxLayout *mainLayout;   // Главный макет (включает панель навигации и содержимое)
    QStackedWidget *stackedWidget; // Виджет для переключения страниц

private:
    QHBoxLayout *navigationLayout; // Макет для панели навигации
    QPushButton *homeButton;
    QPushButton *profileButton;
    QPushButton *aboutButton;

private slots:
    void onHomeClicked();
    void onProfileClicked();
    void onAboutClicked();
};

#endif // BASEPAGE_H
