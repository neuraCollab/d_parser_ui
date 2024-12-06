# Базовый образ для сборки Qt-приложений
FROM ubuntu:22.04

# Установка переменной окружения для предотвращения интерактивных запросов
ENV DEBIAN_FRONTEND=noninteractive 
ENV WAYLAND_DISPLAY=wayland-0

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
    libqt5gui5 && apt-get clean && rm -rf /var/lib/apt/lists/* 

ENV QT_DEBUG_PLUGINS=1
# Указание рабочей директории
WORKDIR /app

# Копирование всех файлов проекта
COPY . /app

# Создание директории для сборки

# Перемещение в директорию сборки и выполнение CMake + Make
WORKDIR /app/DataParserApp
RUN rm -rf build && mkdir build && cd build && cmake .. && make

# Указать порт для клиента (если необходимо)
EXPOSE 3000

# Команда для запуска приложения
CMD ["./DataParserApp"]
