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


}
