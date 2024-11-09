#include "profile.h"
#include "qstackedwidget.h"
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

Profile::Profile(QWidget *parent) : QWidget(parent) {
    // Основная компоновка страницы
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Горизонтальная компоновка для размещения кнопки слева
    QHBoxLayout *topLayout = new QHBoxLayout;

    // Создаем кнопку "Назад на главную"
    QPushButton *backToHomeButton = new QPushButton("Назад на главную", this);
    backToHomeButton->setStyleSheet("background-color: white; color: black;"); // Устанавливаем стиль кнопки

    // Подключаем слот для обработки нажатия
    connect(backToHomeButton, &QPushButton::clicked, this, &Profile::onBackToHomeButtonClicked);

    // Добавляем кнопку в левую часть горизонтальной компоновки
    topLayout->addWidget(backToHomeButton, 0, Qt::AlignLeft);

    // Добавляем отступ в правую часть горизонтальной компоновки, чтобы кнопка оставалась слева
    topLayout->addStretch();

    // Добавляем горизонтальную компоновку в основную вертикальную
    layout->addLayout(topLayout);

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText("Введите описание заказа...");
    layout->addWidget(descriptionEdit);

    // Поле для загрузки файлов
    QPushButton *uploadFilesButton = new QPushButton("Загрузить файлы", this);
    connect(uploadFilesButton, &QPushButton::clicked, [this]() {
        QStringList fileNames = QFileDialog::getOpenFileNames(this, "Выберите файлы", QString(), "CSV Files (*.csv);;JSON Files (*.json)");
        if (!fileNames.isEmpty()) {
            QMessageBox::information(this, "Файлы загружены", "Выбранные файлы: " + fileNames.join(", "));
        }
    });
    layout->addWidget(uploadFilesButton);

    submitButton = new QPushButton("Отправить заказ", this);
    connect(submitButton, &QPushButton::clicked, this, &Profile::onSubmitButtonClicked);
    layout->addWidget(submitButton);

    setLayout(layout);
}

void Profile::onSubmitButtonClicked() {
    QString description = descriptionEdit->toPlainText();
    if (description.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите описание заказа.");
        return;
    }

    QMessageBox::information(this, "Успех", "Ваш заказ успешно отправлен!");
}

// Слот для кнопки возврата на главную страницу
void Profile::onBackToHomeButtonClicked() {
    QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(parent());
    if (stackedWidget) {
        stackedWidget->setCurrentIndex(0); // Переключаемся на главную страницу
    }
}
