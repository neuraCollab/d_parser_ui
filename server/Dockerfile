# Базовый образ
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive 
# Установить основные зависимости
RUN apt-get update && apt-get install -y \
    curl \
    zip \
    unzip \
    tar \
    git \
    build-essential \
    cmake \
    libssl-dev \
    qtbase5-dev \
    qtchooser \
    qt5-qmake \
    pkg-config \
    qttools5-dev-tools \
    && apt-get clean

# Установить vcpkg
WORKDIR /app
RUN git clone https://github.com/microsoft/vcpkg.git && \
    cd vcpkg && \
    ./bootstrap-vcpkg.sh

# Установить зависимости из vcpkg.json
COPY ./QtServerApp/vcpkg.json /app/vcpkg.json
RUN /app/vcpkg/vcpkg install 

# Настроить переменные окружения для vcpkg
ENV VCPKG_ROOT=/app/vcpkg
ENV PATH="$VCPKG_ROOT:$PATH"
ENV CMAKE_TOOLCHAIN_FILE=/app/vcpkg/scripts/buildsystems/vcpkg.cmake

# Копировать проект в контейнер
WORKDIR /app/server/QtServerApp
COPY ./QtServerApp/CMakeUserPresets.json /app/server/QtServerApp/CMakeUserPresets.json
# RUN ls -la /app/server/QtServerApp/QtServerApp && sleep 10

# Настроить CMake, используя CMakePresets.json
RUN cd /app/server/QtServerApp/ && cmake --presets "default"

# Собрать проект
RUN cmake --build build --config Release

# Удалить временные файлы сборки, чтобы уменьшить размер образа
RUN rm -rf ./build

# Экспортировать переменные среды из .env, если требуется
# ENV ENV_VARIABLE=value

# Указать команду для запуска сервера
CMD ["./build/QtServerApp"]
