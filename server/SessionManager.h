#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QDateTime>
#include <QVariantMap>

class SessionManager {
public:
    QString generateToken(const QString& username);
    bool createSession(int userId, const QString& token, const QDateTime& expiresAt);
    QVariantMap getSession(const QString& token);
    bool deleteSession(const QString& token);
};

#endif // SESSIONMANAGER_H
