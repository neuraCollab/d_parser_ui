#include "aboutpage.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>

AboutPage::AboutPage(QWidget *parent) : QWidget(parent) {
    // Основная компоновка страницы
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Горизонтальная компоновка для размещения кнопки "Назад на главную"
    QHBoxLayout *topLayout = new QHBoxLayout;

    // Создаем кнопку "Назад на главную"
    backToHomeButton = new QPushButton("Назад на главную", this);
    backToHomeButton->setStyleSheet("background-color: white; color: black; padding: 5px 15px; font-size: 14px;");

    // Подключаем слот для обработки нажатия
    connect(backToHomeButton, &QPushButton::clicked, this, &AboutPage::onBackToHomeButtonClicked);

    // Добавляем кнопку в левую часть горизонтальной компоновки
    topLayout->addWidget(backToHomeButton, 0, Qt::AlignLeft);

    // Добавляем отступ в правую часть горизонтальной компоновки
    topLayout->addStretch();

    // Добавляем горизонтальную компоновку в основную вертикальную
    mainLayout->addLayout(topLayout);

    // Контент страницы "О нас"
    QLabel *titleLabel = new QLabel("О нас", this);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: black; padding: 20px;");
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel *descriptionLabel = new QLabel(
        "HWParser - это мощный инструмент для анализа данных, который помогает упрощать процессы обработки и визуализации данных.\n\n"
        "Мы предлагаем простоту, скорость и высокую точность в работе с большими объемами информации. "
        "Наш продукт идеально подходит для всех, кто ищет надежное решение для работы с данными.",
        this);
    descriptionLabel->setStyleSheet("font-size: 16px; color: #555; padding: 20px;");
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // Добавляем элементы на страницу
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(descriptionLabel);

    // Добавляем отступ внизу страницы
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void AboutPage::onBackToHomeButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget *>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0); // Переключаемся на главную страницу
    }
}
