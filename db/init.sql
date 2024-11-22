-- Таблица пользователей
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username VARCHAR(255) NOT NULL UNIQUE,
    password_hash VARCHAR(255) NOT NULL,
    email VARCHAR(255) NOT NULL UNIQUE,
    client_key VARCHAR(255),
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- Моковые данные для пользователей
INSERT INTO users (username, password_hash, email, client_key)
VALUES 
    ('john_doe', 'hashed_password1', 'john.doe@example.com', 'client_key_123'),
    ('jane_smith', 'hashed_password2', 'jane.smith@example.com', 'client_key_456'),
    ('alice_jones', 'hashed_password3', 'alice.jones@example.com', 'client_key_789');

-- Таблица ссылок
CREATE TABLE links (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    url TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users (id)
);

-- Моковые данные для ссылок
INSERT INTO links (user_id, url)
VALUES 
    (1, 'http://example.com/page1'),
    (1, 'http://example.com/page2'),
    (2, 'http://example.org/page1');

-- Таблица конфигураций сайтов
CREATE TABLE site_configs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    config TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users (id)
);

-- Моковые данные для конфигураций сайтов
INSERT INTO site_configs (user_id, config)
VALUES 
    (1, '{"setting": "value1"}'),
    (2, '{"setting": "value2"}');

-- Таблица сессий
CREATE TABLE sessions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    token VARCHAR(255) NOT NULL UNIQUE,
    expires_at DATETIME NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users (id)
);

-- Моковые данные для сессий
INSERT INTO sessions (user_id, token, expires_at)
VALUES 
    (1, 'session_token_123', '2024-12-31 23:59:59'),
    (2, 'session_token_456', '2024-12-31 23:59:59');
