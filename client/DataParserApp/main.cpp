#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window; // Создание экземпляра MainWindow
    window.show(); // Отображение главного окна

    return app.exec();
}
