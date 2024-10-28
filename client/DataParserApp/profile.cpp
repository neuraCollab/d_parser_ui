#include "profile.h"
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

Profile::Profile(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;

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
