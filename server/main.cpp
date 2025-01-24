#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include "server.h"
#include <QDir> // Добавляем этот заголовок
#include "database.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "server_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // Инициализация базы данных
    Database();

    // Создаем директорию для хранения файлов
    QDir dir("uploads");
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Запуск сервера
    Server server;

    return a.exec();
}
