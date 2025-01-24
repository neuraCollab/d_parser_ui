#include <QCoreApplication>
#include "DatabaseManager.h"
#include "SessionManager.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    DatabaseManager dbManager;
    if (!dbManager.open()) {
        return -1;
    }

    SessionManager sessionManager;
    QString token = sessionManager.generateToken("testuser");

    // Тест создания сессии
    int userId = 1; // Идентификатор пользователя для теста
    QDateTime expiresAt = QDateTime::currentDateTime().addDays(1);
    if (sessionManager.createSession(userId, token, expiresAt)) {
        qDebug() << "Сессия создана. Токен:" << token;
    }

    // Тест получения сессии
    QVariantMap sessionInfo = sessionManager.getSession(token);
    if (!sessionInfo.isEmpty()) {
        qDebug() << "Сессия найдена:" << sessionInfo;
    }

    // Тест удаления сессии
    if (sessionManager.deleteSession(token)) {
        qDebug() << "Сессия успешно удалена.";
    }

    dbManager.close();
    return a.exec();
}
