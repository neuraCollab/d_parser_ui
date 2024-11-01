QT += core network sql
CONFIG += c++11

SOURCES += main.cpp \
           DatabaseManager.cpp \
           SessionManager.cpp \
           FileParser.cpp \
           HttpServer.cpp

HEADERS += DatabaseManager.h \
           SessionManager.h \
           FileParser.h \
           HttpServer.h

