CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    login VARCHAR(32) NOT NULL UNIQUE,
    salt VARCHAR(64) NOT NULL UNIQUE,
    hash VARCHAR(64) NOT NULL
);

CREATE TABLE users_profiles (
    user_id INTEGER PRIMARY KEY NOT NULL,
    first_name VARCHAR(64),
    second_name VARCHAR(64),
    status VARCHAR(32),
    register_time CHAR(19),

    FOREIGN KEY (user_id) REFERENCES users (id)
        ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TRIGGER add_profile AFTER INSERT
    ON users
BEGIN
    INSERT INTO users_profiles(user_id, register_time) VALUES
        (NEW.id, datetime('now', 'localtime'));
END;

CREATE TABLE black_lists (
    user_id INTEGER PRIMARY KEY NOT NULL,
    banned_id INTEGER NOT NULL,
    reason VARCHAR(32),

    FOREIGN KEY (user_id) REFERENCES users (id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (banned_id) REFERENCES users (id)
        ON DELETE CASCADE ON UPDATE CASCADE,

    CHECK(user_id != banned_id)
);

CREATE TABLE contact_groups (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(64) NOT NULL
);

CREATE TABLE contact_lists (
    user_id INTEGER PRIMARY KEY NOT NULL,
    contact_id INTEGER NOT NULL,
    group_id INTEGER,

    FOREIGN KEY (user_id) REFERENCES users (id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (contact_id) REFERENCES users (id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (group_id) REFERENCES contact_groups (id)
        ON DELETE CASCADE ON UPDATE CASCADE,

    CHECK(user_id != contact_id)
);

CREATE TABLE chats (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    type INTEGER NOT NULL,
    name VARCHAR(64) NOT NULL,
    description VARCHAR(128)
);

CREATE TABLE user_chats (
    user_id INTEGER NOT NULL,
    chat_id INTEGER NOT NULL,
    role INTEGER DEFAULT 1,

    FOREIGN KEY (user_id) REFERENCES users (id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (chat_id) REFERENCES chats (id)
        ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    chat_id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    type INTEGER NOT NULL,
    send_time CHAR(19) NOT NULL,
    content VARCHAR(64) NOT NULL,

    FOREIGN KEY (user_id) REFERENCES users (id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (chat_id) REFERENCES chats (id)
        ON DELETE CASCADE ON UPDATE CASCADE
);

-- register users
INSERT INTO users (login, salt, hash) VALUES
    ('oafanasiev', 'qwerty', 'qwerty'),
    ('abalabin', 'asdfgh', 'asdfgh'),
    ('trohalska', 'zxcvbn', 'zxcvbn'),
    ('yburienkov', 'lpmkoj', 'lpmkoj');

SELECT * FROM users;
SELECT * FROM users INNER JOIN users_profiles ON id = user_id;

UPDATE (SELECT * FROM users INNER JOIN users_profiles ON id = user_id)
SET first_name = login, second_name = login, status = login;

-- UPDATE users_profiles SET first_name = (SELECT login FROM users WHERE users.id = users_profiles.user_id);
-- UPDATE users_profiles SET second_name = (SELECT login FROM users WHERE users.id = users_profiles.user_id);
-- UPDATE users_profiles SET status = (SELECT login FROM users WHERE users.id = users_profiles.user_id);

-- .headers on
-- .mode column
