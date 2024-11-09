#include "aboutpage.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>

AboutPage::AboutPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Добавляем кнопку "Назад на главную страницу"
    backToHomeButton = new QPushButton("Назад на главную", this);
    connect(backToHomeButton, &QPushButton::clicked, this, &AboutPage::onBackToHomeButtonClicked);
    layout->addWidget(backToHomeButton);

    setLayout(layout);
}

void AboutPage::onBackToHomeButtonClicked() {
    // Находим QStackedWidget и переключаемся на начальную страницу (предполагаем, что индекс 0 — HomePage)
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0); // Переключаемся на главную страницу
    }
}
