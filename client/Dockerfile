# Базовый образ для сборки Qt-приложений
FROM ubuntu:22.04

# Установка необходимых зависимостей
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qtbase5-dev \
    qt5-qmake \
    qttools5-dev-tools \
    libqt5widgets5 \
    libqt5network5 \
    g++ \
    && apt-get clean

# Указание рабочей директории
WORKDIR /app

# Копирование всех файлов проекта
COPY . /app

# Создание директории для сборки
RUN mkdir build

# Перемещение в директорию сборки и выполнение CMake + Make
WORKDIR /app/build
RUN cmake .. && make

# Указать порт для клиента (если необходимо)
EXPOSE 3000

# Команда для запуска приложения
CMD ["./DataParserApp"]
