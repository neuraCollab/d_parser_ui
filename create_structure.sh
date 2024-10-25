#!/bin/bash

# Устанавливаем переменную окружения PROJECT_ROOT, если она не задана
PROJECT_ROOT=${PROJECT_ROOT:-"."}

# Создание корневого каталога проекта
mkdir -p "$PROJECT_ROOT"/{client,server,parser,db,k8s,logs}

# Создание основных файлов и подкаталогов для client
mkdir -p "$PROJECT_ROOT"/client/{src,include}
touch "$PROJECT_ROOT"/client/CMakeLists.txt
touch "$PROJECT_ROOT"/client/src/main.cpp

# Создание основных файлов и подкаталогов для server
mkdir -p "$PROJECT_ROOT"/server/{src,include}
touch "$PROJECT_ROOT"/server/CMakeLists.txt
touch "$PROJECT_ROOT"/server/src/main.cpp
touch "$PROJECT_ROOT"/server/Dockerfile

# Создание основных файлов для parser
mkdir -p "$PROJECT_ROOT"/parser/src
touch "$PROJECT_ROOT"/parser/Dockerfile

# Создание файлов для базы данных
touch "$PROJECT_ROOT"/db/init.sql

# Создание файлов для Kubernetes
touch "$PROJECT_ROOT"/k8s/deployment.yaml
touch "$PROJECT_ROOT"/k8s/service.yaml
touch "$PROJECT_ROOT"/k8s/ingress.yaml

# Создание файла для логов
touch "$PROJECT_ROOT"/logs/server.log

# Создание env-файла
touch "$PROJECT_ROOT"/.env

# Создание docker-compose.yml
cat <<EOL > "$PROJECT_ROOT"/docker-compose.yml
version: '3'
services:
  client:
    build: ./client
    container_name: client_app
    ports:
      - "3000:3000"
  server:
    build: ./server
    container_name: server_app
    ports:
      - "8080:8080"
    environment:
      - DB_HOST=db
      - DB_USER=root
      - DB_PASS=password
  parser:
    build: ./parser
    container_name: parser_app
  db:
    image: mysql:5.7
    container_name: db
    environment:
      MYSQL_ROOT_PASSWORD: password
    volumes:
      - ./db/init.sql:/docker-entrypoint-initdb.d/init.sql
    ports:
      - "3306:3306"
EOL

echo "Project structure created successfully at: $PROJECT_ROOT"
