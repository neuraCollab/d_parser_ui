#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QString>

class FileParser {
public:
    bool parseAndStoreLinks(const QString& filePath, int userId);
    bool storeSiteConfig(const QString& configFilePath, int userId);
};

#endif // FILEPARSER_H
