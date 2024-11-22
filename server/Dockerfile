# Базовый образ для сборки Qt-приложений
FROM ubuntu:22.04

# Установить необходимые зависимости
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qtbase5-dev \
    qt5-qmake \
    libqt5sql5 \
    libqt5network5 \
    g++ \
    curl \
    && apt-get clean

# Указать рабочую директорию
WORKDIR /app

# Копировать весь проект в контейнер
COPY . /app

# Создать директорию для сборки
RUN mkdir build

# Перейти в директорию сборки, выполнить CMake и сборку
WORKDIR /app/build
RUN cmake .. && make

# Указать порт, который будет использовать сервер
EXPOSE 8080

# Команда для запуска приложения
CMD ["./QtServerApp"]
