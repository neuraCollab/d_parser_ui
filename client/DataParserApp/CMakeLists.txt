cmake_minimum_required(VERSION 3.5)

project(DataParserApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск нужных компонентов Qt, включая Network
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)

# Для Qt6
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        login.h login.cpp
        homepage.h homepage.cpp
        register.h register.cpp
        profile.h profile.cpp
        aboutpage.h aboutpage.cpp
        authmanager.h authmanager.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DataParserApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        basepage.h basepage.cpp
    )
else()
    if(ANDROID)
        add_library(DataParserApp SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(DataParserApp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Линковка с Qt Widgets и Network
target_link_libraries(DataParserApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

# Опции для работы с macOS, iOS и Windows (если нужно)
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DataParserApp)
endif()

set_target_properties(DataParserApp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DataParserApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DataParserApp)
endif()
