FROM ubuntu:16.04

ENV QT_VERSION v5.9.1
ENV QT_CREATOR_VERSION v4.3.1

# Build prerequisites
RUN apt-get -y update && apt-get -y install qtbase5-dev \
	libxcb-xinerama0-dev \
	build-essential \
	python

# Other useful tools
RUN apt-get -y update && apt-get -y install tmux \
	wget \
	zip \
	git \
	vim

# Simple root password in case we want to customize the container
RUN echo "root:root" | chpasswd

RUN useradd -G video -ms /bin/bash user


WORKDIR /qt/build


USER user

WORKDIR /qt

# Указание рабочей директории
WORKDIR /app

# Копирование всех файлов проекта
COPY . /app

# Перемещение в директорию сборки и выполнение CMake + Make
WORKDIR /app/DataParserApp
RUN rm -rf build && mkdir build && cd build && cmake .. && make

# Указать порт для клиента (если необходимо)
EXPOSE 3000

# Команда для запуска приложения
CMD ["./build/DataParserApp"]
