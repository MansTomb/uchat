{ "json_type": 0, "login": "tatat", "hash": "jfhgkajdfhgkfdj"}
{ "json_type": 0, "login": "trohalska", "hash": "444"}

{ "json_type": 3, "login": "tatat", "hash": "jfhgkajdfhgkfdj"}
{ "json_type": 3, "login": "trohalska", "hash": "444"}

{ "json_type": 9, "login": "trohalska", "hash": "444", "new_hash": "7777"}

{ "json_type": 22, "uid1": 11, "uid2": 12 }

{ "json_type": 29, "uid": 11, "chat_id": 4, "type": 1, "content": "Hello, dear friend!"}

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (%i, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (%i, (SELECT max(id) FROM chats), 1);
SELECT max(id) FROM chats;


SELECT uc.user_id, up.email
FROM users_chats AS uc
    JOIN users_profiles AS up
        ON uc.user_id = up.user_id AND uc.chat_id = '%i' AND uc.user_id != '%i'


FROM users_chats WHERE chat_id = '%i' AND user_id != '%i';
