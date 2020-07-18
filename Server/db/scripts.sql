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

CREATE TABLE IF NOT EXISTS users_groups (
    user_id INTEGER NOT NULL,
    group_id INTEGER NOT NULL,

    PRIMARY KEY (user_id, group_id)
);

CREATE TABLE IF NOT EXISTS contacts_lists (
    user_id INTEGER NOT NULL,
    contact_id INTEGER NOT NULL,
    group_id INTEGER DEFAULT 0,

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
INSERT INTO users VALUES (NULL, '__NEW_USER_LOGIN__', '__NEW_USER_PASSWORD__');

-- авторизация
SELECT * FROM users WHERE login = '__NEW_USER_LOGIN__';

-- удаление юзера
DELETE FROM users WHERE id = __UID__ AND hash = __HASH__;

-- изменение пароля
UPDATE users SET hash = '__NEW_USER_PASSWORD__' WHERE id = __UID__;

-- получение профиля
SELECT * FROM users_profiles WHERE user_id = __UID__;

-- обновление профиля
UPDATE users_profiles SET first_name = '__NEW_FIRST_NAME__' WHERE user_id = __UID__;
UPDATE users_profiles SET second_name = '__NEW_SECOND_NAME__' WHERE user_id = __UID__;
UPDATE users_profiles SET email = '__NEW_EMAIL__' WHERE user_id = __UID__;
UPDATE users_profiles SET status = '__NEW_STATUS__' WHERE user_id = __UID__;

-- создание новой группы контактов
INSERT INTO contacts_groups VALUES (NULL, '__NEW_GROUP_NAME__');

-- добавление новой группы контактов у юзера
INSERT INTO users_groups VALUES (__UID__, __GID__);

-- добавление нового контакта
INSERT INTO contacts_lists VALUES (__UID__, __COID__, __GID__); -- __UID__, __COID__, NULL

-- удаление из контактов
DELETE FROM contacts_lists WHERE user_id = __UID__ AND contact_id = __COID__;

-- добавление контакта в группу
UPDATE contacts_lists SET group_id = GROUP_ID WHERE user_id = __UID__ AND contact_id = __COID__;

-- удаление контакта из группы
UPDATE contacts_lists SET group_id = NULL WHERE user_id = __UID__ AND contact_id = __COID__;

-- создание чата
INSERT INTO chats VALUES (NULL, __CHAT_TYPE__, '__NEW_CHAT_NAME__');

-- добавление юзера в чат
INSERT INTO users_chats VALUES (__UID__, __CID__);

-- изменение роли (бан / выход / новый админ / новый создатель)
UPDATE users_chats SET role = __NEW_ROLE__ WHERE user_id = __UID__ AND chat_id = __CID__;

-- отправка сообщения
INSERT INTO messages VALUES (NULL, __UID__, __CID__, __TYPE__, datetime('now', 'localtime'), __CONTENT__);

-- удаление сообщения
DELETE FROM messages WHERE id = __MID__;

-- -- -- -- -- -- -- -- -- -- комплексные запросы -- -- -- -- -- -- -- -- -- --

-- загрузка информации о клиенте
SELECT u.id, u.login,
    up.first_name, up.second_name, up.email, up.status,
    uns.sound, uns.visual, uns.email
FROM users AS u
    JOIN users_profiles AS up
        ON u.id = up.user_id AND u.id = __UID__
    JOIN users_notify_settings AS uns
        ON u.id = uns.user_id;

SELECT up.first_name, up.second_name, up.email, up.status, uns.sound, uns.visual, uns.email FROM users_profiles AS up JOIN users_notify_settings AS uns ON up.user_id = __UID__ AND up.user_id = uns.user_id;
SELECT u.id, u.login, up.first_name, up.second_name, up.email, up.status, uns.sound, uns.visual, uns.email FROM users AS u JOIN users_profiles AS up ON u.id = up.user_id AND u.id = __UID__ JOIN users_notify_settings AS uns ON u.id = uns.user_id;

-- создание личной переписки
INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (__UID1__, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (__UID2__, (SELECT max(id) FROM chats), 1);

-- создание нового группового чата / канала
INSERT INTO chats VALUES (NULL, __CHAT_TYPE__, '__NEW_CHAT_NAME__');
INSERT INTO users_chats VALUES (__UID__, last_insert_rowid(), 2);

-- загрузка групп контактов юзера
SELECT ug.group_id, cg.name FROM users_groups AS ug
    JOIN contacts_groups AS cg
        ON ug.user_id = __UID__ AND cg.id = ug.group_id;

SELECT ug.group_id, cg.name FROM users_groups AS ug JOIN contacts_groups AS cg ON ug.user_id = __UID__ AND cg.id = ug.group_id;

-- загрузка контактов юзера
SELECT cl.contact_id, u.login, up.first_name, up.second_name, up.email, up.status, cl.group_id
FROM contacts_lists AS cl
    JOIN users AS u
        ON cl.contact_id = u.id AND cl.user_id = __UID__
    JOIN users_profiles AS up
        ON cl.contact_id = up.user_id;

SELECT cl.contact_id, u.login, up.first_name, up.second_name, up.email, up.status, cl.group_id FROM contacts_lists AS cl JOIN users AS u ON cl.contact_id = u.id AND cl.user_id = __UID__ JOIN users_profiles AS up ON cl.contact_id = up.user_id;

-- загрузка активных чатов юзера. подтягивает логин собеседника в название чатика, если лс чат
SELECT uc.chat_id, uc.role, c.type,
CASE
    WHEN c.type = 1
        THEN (SELECT u.login FROM users AS u
                JOIN users_chats AS uc
                    ON uc.chat_id = c.id AND uc.user_id != __UID__ AND uc.user_id = u.id)
    ELSE c.name
END name
FROM users_chats AS uc
    JOIN chats AS c
        ON uc.chat_id = c.id AND uc.user_id = __UID__ AND uc.role > 0;

SELECT uc.chat_id, uc.role, c.type, CASE WHEN c.type = 1 THEN (SELECT u.login FROM users AS u JOIN users_chats AS uc ON uc.chat_id = c.id AND uc.user_id != __UID__ AND uc.user_id = u.id) ELSE c.name END name FROM users_chats AS uc JOIN chats AS c ON uc.chat_id = c.id AND uc.user_id = __UID__ AND uc.role > 0;

-- загрузка сообщений в чате
SELECT * FROM messages WHERE chat_id = __CID__ ORDER BY id DESC LIMIT 50;

-- отправка сообщения
INSERT INTO messages VALUES (NULL, __UID__, __CID__, __TYPE__, datetime('now', 'localtime'), __CONTENT__);
SELECT user_id FROM users_chats WHERE chat_id = __CID__ AND user_id != __UID__;

-- найти id чата между двумя юзерами
SELECT c.id, uc1.role FROM users_chats AS uc1
    JOIN users_chats AS uc2
        ON uc1.user_id = __UID1__ AND uc2.user_id = __UID2__
            AND uc1.chat_id = uc2.chat_id
    JOIN chats AS c
        ON c.type = 1 AND uc1.chat_id = c.id;

SELECT c.id, uc1.role FROM users_chats AS uc1 JOIN users_chats AS uc2 ON uc1.user_id = __UID1__ AND uc2.user_id = __UID2__ AND uc1.chat_id = uc2.chat_id JOIN chats AS c ON c.type = 1 AND uc1.chat_id = c.id;

-- вибрати дані для відправки повідомлень
SELECT uc.user_id, up.email
FROM users_chats AS uc
    JOIN users_profiles AS up
        ON uc.user_id = up.user_id AND uc.chat_id = __CID__ AND uc.user_id != __UID__;

SELECT uc.user_id, up.email FROM users_chats AS uc JOIN users_profiles AS up ON uc.user_id = up.user_id AND uc.chat_id = __CID__ AND uc.user_id != __UID__;
