cmake_minimum_required(VERSION 3.19)
project(server LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core  Sql LinguistTools Network HttpServer)

qt_standard_project_setup()

qt_add_executable(server
    main.cpp
    server.h server.cpp
    database.h database.cpp
)

target_link_libraries(server
    PRIVATE
        Qt6::Core
        Qt::Sql
        Qt6::Network
        Qt6::HttpServer
        OpenSSL::SSL
        OpenSSL::Crypto
)

include(GNUInstallDirs)

install(TARGETS server
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET server
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
