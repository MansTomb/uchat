-- users profile block

CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    login VARCHAR(32) NOT NULL UNIQUE,
    salt VARCHAR(64) NOT NULL UNIQUE,
    hash VARCHAR(64) NOT NULL
);

CREATE TABLE IF NOT EXISTS users_profiles (
    user_id INTEGER PRIMARY KEY NOT NULL,
    first_name VARCHAR(64),
    second_name VARCHAR(64),
    status VARCHAR(32),
    register_time CHAR(19)
);

CREATE TRIGGER IF NOT EXISTS add_profile AFTER INSERT
    ON users
BEGIN
    INSERT INTO users_profiles (user_id, register_time) VALUES
        (NEW.id, datetime('now', 'localtime'));
END;

CREATE TRIGGER IF NOT EXISTS del_profile AFTER DELETE
    ON users
BEGIN
    DELETE FROM users_profiles
    WHERE user_id = OLD.id;
END;

-- user contacts block

CREATE TABLE IF NOT EXISTS contact_groups (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(64) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS contact_lists (
    user_id INTEGER NOT NULL,
    contact_id INTEGER NOT NULL,
    group_id INTEGER,

    PRIMARY KEY (user_id, contact_id)
);

-- chats block

CREATE TABLE IF NOT EXISTS chats (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    type INTEGER NOT NULL,
    name VARCHAR(64) NOT NULL
);

CREATE TABLE IF NOT EXISTS user_chats (
    user_id INTEGER NOT NULL,
    chat_id INTEGER NOT NULL,
    role INTEGER DEFAULT 1,

    PRIMARY KEY (user_id, char_id)
);

CREATE TABLE IF NOT EXISTS messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    chat_id INTEGER NOT NULL,
    type INTEGER NOT NULL,
    send_time CHAR(19) NOT NULL,
    content VARCHAR(64) NOT NULL
);

CREATE TABLE IF NOT EXISTS block_lists (
    chat_id INTEGER NOT NULL,
    banned_id INTEGER NOT NULL,

    PRIMARY KEY (chat_id, banned_id)
);

-- register users

INSERT INTO users VALUES
    (NULL, 'abalabin', 'qwerty', 'qwerty'),
    (NULL, 'oafanasiev', 'asdfgh', 'asdfgh'),
    (NULL, 'trohalska', 'zxcvbn', 'zxcvbn'),
    (NULL, 'yburienkov', 'lpmkoj', 'lpmkoj');

SELECT * FROM users;
SELECT * FROM users JOIN users_profiles ON id = user_id;

-- UPDATE users_profiles SET first_name = (SELECT login FROM users WHERE users.id = users_profiles.user_id);
-- UPDATE users_profiles SET second_name = (SELECT login FROM users WHERE users.id = users_profiles.user_id);
-- UPDATE users_profiles SET status = (SELECT login FROM users WHERE users.id = users_profiles.user_id);

-- .headers on
-- .mode column
