#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Инициализация приложения

    MainWindow window; // Создание экземпляра главного окна
    window.show(); // Отображение главного окна

    return app.exec(); // Запуск основного цикла приложения
}
