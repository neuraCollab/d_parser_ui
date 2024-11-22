#include "FileParser.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>

// Функция для обработки и сохранения ссылок из файла Excel
bool FileParser::parseAndStoreLinks(const QString& filePath, int userId) {
    // Здесь предполагается использование pandas для чтения данных из Excel.
    // Этот код может быть выполнен в Python или интегрирован через внешние библиотеки.
    // Однако, для Qt без использования pandas можно использовать QtXlsxWriter или другую библиотеку.

    // Пример реализации для учебных целей
    QSqlQuery query;
    query.prepare("INSERT INTO links (user_id, url) VALUES (:userId, :url)");

    // Допустим, мы уже извлекли URL-ы и записали их в переменную urls (список строк).
    QStringList urls = {"http://example.com", "http://another-example.com"};

    for (const QString &url : urls) {
        query.bindValue(":userId", userId);
        query.bindValue(":url", url);

        if (!query.exec()) {
            qDebug() << "Ошибка добавления ссылки:" << query.lastError().text();
            return false;
        }
    }
    return true;
}

// Функция для сохранения конфигураций сайтов из ZIP-файла
bool FileParser::storeSiteConfig(const QString& configFilePath, int userId) {
    QFile file(configFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Ошибка открытия файла конфигурации";
        return false;
    }
    QByteArray configData = file.readAll();
    file.close();

    QSqlQuery query;
    query.prepare("INSERT INTO site_configs (user_id, config_data) VALUES (:userId, :configData)");
    query.bindValue(":userId", userId);
    query.bindValue(":configData", configData);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления конфигурации сайта:" << query.lastError().text();
        return false;
    }
    return true;
}
