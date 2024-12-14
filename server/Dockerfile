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
COPY ./vcpkg.json /app/vcpkg.json
RUN /app/vcpkg/vcpkg install 

# Настроить переменные окружения для vcpkg
ENV VCPKG_ROOT=/app/vcpkg
ENV PATH="$VCPKG_ROOT:$PATH"
ENV CMAKE_TOOLCHAIN_FILE=/app/vcpkg/scripts/buildsystems/vcpkg.cmake

# Копировать проект в контейнер
WORKDIR /app/server/
COPY . .

# Настроить права на исполняемые файлы
RUN chmod +x /app/vcpkg/vcpkg

# Проверить наличие файлов в папке
RUN ls -la && sleep 1

# Настроить CMake и собрать проект
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/app/vcpkg/scripts/buildsystems/vcpkg.cmake && \
    cmake --build build --config Release

# Удалить временные файлы сборки, чтобы уменьшить размер образа
RUN rm -rf /app/server/build

# Указать команду для запуска сервера
CMD ["./build/QtServerApp"]
