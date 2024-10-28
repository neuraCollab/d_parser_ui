#include "mainpage.h"
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

MainPage::MainPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;

    fileLineEdit = new QLineEdit(this);
    fileLineEdit->setPlaceholderText("Select CSV file");
    layout->addWidget(fileLineEdit);

    uploadButton = new QPushButton("Upload CSV", this);
    layout->addWidget(uploadButton);

    connect(uploadButton, &QPushButton::clicked, this, &MainPage::onUploadButtonClicked);

    setLayout(layout);
}

void MainPage::onUploadButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open CSV File", QString(), "CSV Files (*.csv);;All Files (*)");
    if (!fileName.isEmpty()) {
        fileLineEdit->setText(fileName);
        QMessageBox::information(this, "File Selected", "You selected: " + fileName);
        // Здесь можно добавить логику обработки CSV файла
    }
}
