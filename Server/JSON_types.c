-- registration
{ "json_type": 0, "login": "tatat", "hash": "jfhgkajdfhgkfdj"}
{ "json_type": 0, "login": "trohalska", "hash": "444"}
{ "json_type": 0, "login": "sasha1", "hash": "oibjktbkaslkbjgfk"}

-- authorization
{ "json_type": 3, "login": "tatat", "hash": "jfhgkajdfhgkfdj"}
{ "json_type": 3, "login": "trohalska", "hash": "444"}
{ "json_type": 3, "login": "sasha1", "hash": "oibjktbkaslkbjgfk"}

-- change_password
{ "json_type": 9, "login": "trohalska", "hash": "444", "new_hash": "7777"}

-- create personal chat
{ "json_type": 22, "uid1": 1, "uid2": 2 }

-- send message
{ "json_type": 29, "uid": 1, "chat_id": 1, "type": 1, "content": "Hello, dear friend!"}

-- add new contact










----------------------------------------------------------------------- SQL
INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (%i, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (%i, (SELECT max(id) FROM chats), 1);
SELECT max(id) FROM chats;

SELECT uc.user_id, up.email
FROM users_chats AS uc
    JOIN users_profiles AS up
        ON uc.user_id = up.user_id AND uc.chat_id = '%i' AND uc.user_id != '%i'


FROM users_chats WHERE chat_id = '%i' AND user_id != '%i';

UPDATE users_profiles SET email='trogalska2208@gmail.com' WHERE user_id=2;
