-- users profile block

CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    login VARCHAR(32) NOT NULL UNIQUE,
    hash VARCHAR(64) NOT NULL
);

CREATE TABLE IF NOT EXISTS users_profiles (
    user_id INTEGER PRIMARY KEY NOT NULL,
    first_name VARCHAR(64) DEFAULT '' NOT NULL,
    second_name VARCHAR(64) DEFAULT '' NOT NULL,
    email VARCHAR(64) DEFAULT '' NOT NULL,
    status VARCHAR(32) DEFAULT '' NOT NULL
);

CREATE TABLE IF NOT EXISTS users_notify_settings (
    user_id INTEGER PRIMARY KEY NOT NULL,
    sound INTEGER NOT NULL,
    visual INTEGER NOT NULL,
    email INTEGER NOT NULL
);

CREATE TRIGGER IF NOT EXISTS add_profile
    AFTER INSERT ON users
BEGIN
    INSERT INTO users_profiles (user_id) VALUES (NEW.id);
    INSERT INTO users_notify_settings VALUES (NEW.id, 1, 1, 1);
END;

CREATE TRIGGER IF NOT EXISTS del_profile
    AFTER DELETE ON users
BEGIN
    DELETE FROM users_profiles WHERE user_id = OLD.id;
    DELETE FROM users_notify_settings WHERE user_id = OLD.id;
END;

-- user contacts block

CREATE TABLE IF NOT EXISTS contacts_groups (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(64) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS contacts_lists (
    user_id INTEGER NOT NULL,
    contact_id INTEGER NOT NULL,
    group_id INTEGER,

    PRIMARY KEY (user_id, contact_id),
    CHECK (user_id != contact_id)
);

-- chats block

CREATE TABLE IF NOT EXISTS chats (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    type INTEGER NOT NULL,
    name VARCHAR(64) NOT NULL
);

CREATE TABLE IF NOT EXISTS users_chats (
    user_id INTEGER NOT NULL,
    chat_id INTEGER NOT NULL,
    role INTEGER DEFAULT 1 NOT NULL,

    PRIMARY KEY (user_id, chat_id)
);

CREATE TABLE IF NOT EXISTS messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    chat_id INTEGER NOT NULL,
    type INTEGER NOT NULL,
    send_time CHAR(19) NOT NULL,
    content VARCHAR(64) NOT NULL
);

-- проверка работы триггеров
SELECT * FROM users
    JOIN users_profiles AS up
        ON id = up.user_id
    JOIN users_notify_settings AS uns
        ON id = uns.user_id;

-- регистрация
INSERT INTO users VALUES (NULL, 'NEW_USER_LOGIN', 'NEW_USER_PASSWORD');

-- авторизация
SELECT * FROM users WHERE login = 'NEW_USER_LOGIN';

-- удаление юзера
DELETE FROM users WHERE id = USER_ID AND hash = HASH;

-- изменение пароля
UPDATE users SET hash = 'STRONG_PASSWORD' WHERE id = USER_ID;

-- получение профиля
SELECT * FROM users_profiles WHERE user_id = USER_ID;

-- обновление профиля
UPDATE users_profiles SET first_name = 'NEW_FIRST_NAME' WHERE user_id = USER_ID;
UPDATE users_profiles SET second_name = 'NEW_SECOND_NAME' WHERE user_id = USER_ID;
UPDATE users_profiles SET email = 'NEW_EMAIL' WHERE user_id = USER_ID;
UPDATE users_profiles SET status = 'NEW_STATUS' WHERE user_id = USER_ID;

-- создание новой группы контактов
INSERT INTO contacts_groups VALUES (NULL, 'NEW_GROUP_NAME');

-- добавление нового контакта
INSERT INTO contacts_lists VALUES (USER_ID, CONTACT_ID, NULL);

-- удаление из контактов
DELETE FROM contacts_lists WHERE user_id = USER_ID AND contact_id = CONTACT_ID;

-- добавление контакта в группу
UPDATE contacts_lists SET group_id = GROUP_ID WHERE user_id = USER_ID AND contact_id = CONTACT_ID;

-- удаление контакта из группы
UPDATE contacts_lists SET group_id = NULL WHERE user_id = USER_ID AND contact_id = CONTACT_ID;

-- создание чата
INSERT INTO chats VALUES (NULL, CHAT_TYPE, 'NEW_CHAT_NAME');

-- добавление юзера в чат
INSERT INTO users_chats VALUES (USER_ID, CHAT_ID);

-- изменение роли (бан / выход / новый админ / новый создатель)
UPDATE users_chats SET role = NEW_ROLE WHERE user_id = USER_ID AND chat_id = CHAT_ID;

-- отправка сообщения
INSERT INTO messages VALUES (NULL, USER_ID, CHAT_ID, TYPE, datetime('now', 'localtime'), CONTENT);

-- удаление сообщения
DELETE FROM messages WHERE id = MESSAGE_ID;

-- -- -- -- -- -- -- -- -- -- комплексные запросы -- -- -- -- -- -- -- -- -- --

-- загрузка информации о клиенте
SELECT u.id, u.login,
    up.first_name, up.second_name, up.email, up.status,
    uns.sound, uns.visual, uns.email
FROM users AS u
    JOIN users_profiles AS up
        ON u.id = up.user_id AND u.id = ID
    JOIN users_notify_settings AS uns
        ON u.id = uns.user_id;

-- создание личной переписки
INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (USER_ID1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (USER_ID2, (SELECT max(id) FROM chats), 1);

-- создание нового группового чата / канала
INSERT INTO chats VALUES (NULL, CHAT_TYPE, 'NEW_CHAT_NAME');
INSERT INTO users_chats VALUES (USER_ID, last_insert_rowid(), 2);

-- загрузка контактов юзера
SELECT cl.contact_id, u.login, up.first_name, up.second_name, up.email, up.status, cl.group_id, cg.name
FROM contacts_lists AS cl
    JOIN users AS u
        ON cl.contact_id = u.id AND cl.user_id = USER_ID
    JOIN users_profiles AS up
        ON cl.contact_id = up.user_id
    LEFT JOIN contacts_groups AS cg
        ON cl.group_id = cg.id;

-- загрузка активных чатов юзера
SELECT uc.chat_id, uc.role, c.type, c.name
FROM users_chats AS uc
    JOIN chats AS c
        ON uc.chat_id = c.id AND uc.user_id = USER_ID AND uc.role > 0;

-- тоже самое, но подтягивает логин собеседника в название чатика
SELECT uc.chat_id, uc.role, c.type,
CASE
    WHEN c.type = 1
        THEN (SELECT u.login FROM users AS u
                JOIN users_chats AS uc
                    ON uc.chat_id = c.id AND uc.user_id != 1 AND uc.user_id = u.id)
    ELSE c.name
END name
FROM users_chats AS uc
    JOIN chats AS c
        ON uc.chat_id = c.id AND uc.user_id = USER_ID AND uc.role > 0;

-- загрузка сообщений в чате
SELECT * FROM messages WHERE chat_id = CHAT_ID ORDER BY id DESC LIMIT 50;

-- отправка сообщения
INSERT INTO messages VALUES (NULL, USER_ID, CHAT_ID, TYPE, datetime('now', 'localtime'), CONTENT);
SELECT user_id FROM users_chats WHERE chat_id = CHAT_ID AND user_id != USER_ID;

-- найти id чата между двумя юзерами
SELECT uc1.chat_id FROM users_chats AS uc1
    JOIN users_chats AS uc2
        ON uc1.user_id = USER_ID1 AND uc2.user_id = USER_ID2
            AND uc1.chat_id = uc2.chat_id
    JOIN chats AS c
        ON c.type = 1;

-- 
SELECT c.id, uc1.role FROM users_chats AS uc1
    JOIN users_chats AS uc2
        ON uc1.user_id = USER_ID1 AND uc2.user_id = USER_ID2
            AND uc1.chat_id = uc2.chat_id
    JOIN chats AS c
        ON c.type = 1 AND uc1.chat_id = c.id;

-- вибрати дані для відправки повідомлень
SELECT uc.user_id, up.email
FROM users_chats AS uc
    JOIN users_profiles AS up
        ON uc.user_id = up.user_id AND uc.chat_id = '%i' AND uc.user_id != '%i';
