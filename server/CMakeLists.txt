# Минимальная версия CMake
cmake_minimum_required(VERSION 3.16)

# Имя проекта
project(QtServerApp LANGUAGES CXX)

# Указать стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указать путь к заголовочным файлам
include_directories(/app/vcpkg/installed/x64-linux/include)

# Find fmt and libenvpp
find_package(fmt CONFIG REQUIRED)
find_package(libenvpp CONFIG REQUIRED)

# Link the libraries to your target
# Найти пакеты Qt 6, envpp и fmt
find_package(Qt6 REQUIRED COMPONENTS Core Network Sql)


# Указать исходные файлы проекта
set(SOURCES
    main.cpp
    DatabaseManager.cpp
    SessionManager.cpp
    FileParser.cpp
    # HttpServer.cpp
)

set(HEADERS
    DatabaseManager.h
    SessionManager.h
    FileParser.h
    # HttpServer.h
)

# Создать исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключить библиотеки к проекту
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Network Qt6::Sql fmt::fmt libenvpp::libenvpp) 
