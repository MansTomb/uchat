-- registration
{ "json_type": 0, "login": "ooo", "hash": "222"}
{ "json_type": 0, "login": "trohalska", "hash": "444"}
{ "json_type": 0, "login": "sasha1", "hash": "oibjktbkaslkbjgfk"}

-- authorization
{ "json_type": 3, "login": "tatat", "hash": "jfhgkajdfhgkfdj"}
{ "json_type": 3, "login": "trohalska", "hash": "444"}
{ "json_type": 3, "login": "sasha1", "hash": "oibjktbkaslkbjgfk"}
{ "json_type": 3, "login": "ooo", "hash": "222"}

-- change_password
{ "json_type": 9, "login": "trohalska", "hash": "7", "new_hash": "444"}

-- create personal chat
{ "json_type": 28, "uid1": 1, "uid2": 2 }

-- send message
{ "json_type": 35, "uid": 1, "chat_id": 1, "type": 1, "content": "Hello, dear friend!"}

-- update profile
{ "json_type": 22, "uid": 3, "friend_login": "tatat"}

-- add new contact
{ "json_type": 22, "uid": 3, "friend_login": "tatat"}

-- del contact
{ "json_type": 25, "uid1": 2, "uid2": 1}







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
