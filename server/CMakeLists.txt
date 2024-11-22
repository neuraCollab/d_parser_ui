# Минимальная версия CMake
cmake_minimum_required(VERSION 3.16)

# Имя проекта
project(QtServerApp LANGUAGES CXX)

# Указать стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти пакеты Qt, которые используются в проекте
find_package(Qt5 REQUIRED COMPONENTS Core Network Sql)

# Указать исходные файлы проекта
set(SOURCES
    main.cpp
    DatabaseManager.cpp
    SessionManager.cpp
    FileParser.cpp
    HttpServer.cpp
)

set(HEADERS
    DatabaseManager.h
    SessionManager.h
    FileParser.h
    HttpServer.h
)

# Создать исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключить библиотеки Qt к проекту
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Network Qt5::Sql)
