-- registration
{ "json_type": 0, "login": "tatat", "hash": ""}
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
{ "json_type": 35, "uid": 2, "chat_id": 3, "type": 1, "content": "Hello, dear friend!"}
-- edit message
{ "json_type": 37, "uid": 2, "chat_id": 3, "mid": 30, "content": "Hello!"}
-- delete message
{ "json_type": 38, "uid": 2, "chat_id": 3, "mid": 30}


-- update profile
{"json_type": 12, "uid": 3, "fname": "", "sname": "", "email": "", "status": "", "snot": 1, "vnot": 1, "enot": 1}

-- add new contact
{ "json_type": 22, "uid": 2, "friend_login": "ooo"}

-- del contact
{ "json_type": 25, "uid1": 2, "uid2": 1}

-- get contact_list
{ "json_type": 16, "uid": 2}

-- get client chats
{ "json_type": 18, "uid": 2}

-- get client chats messages
{ "json_type": 20, "uid": 2, "cid": 1}





----------------------------------------------------------------------- SQL
INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (%i, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (%i, (SELECT max(id) FROM chats), 1);
SELECT max(id) FROM chats;

SELECT uc.user_id
FROM users_chats AS uc
    JOIN users_profiles AS up
        ON uc.user_id = up.user_id AND uc.chat_id = '%i' AND uc.user_id != '%i'


FROM users_chats WHERE chat_id = '%i' AND user_id != '%i';

UPDATE users_profiles SET email='trogalska2208@gmail.com' WHERE user_id=2;

SELECT uc.user_id, c.type
FROM users_chats AS uc
    JOIN chats AS c
        ON uc.chat_id = c.id
        WHERE uc.chat_id == %i and uc.role > 0;

SELECT uns.email, up.email
FROM users_notify_settings AS uns
    JOIN users_profiles AS up
        ON uns.user_id = up.user_id
        WHERE up.user_id == %i

SELECT m.user_id, u.login, m.send_time, m.content
FROM messages AS m
    JOIN users AS u
        ON m.user_id = u.id
        WHERE m.chat_id == %i


SELECT * FROM
(SELECT m.user_id, u.login, m.send_time, m.content
             FROM messages AS m JOIN users AS u ON m.user_id = u.id
             ORDER BY m.send_time DESC LIMIT 5
             WHERE m.chat_id = %i)
ORDER BY send_time ASC;

UPDATE (SELECT * FROM messages WHERE id=%i) SET content='%s';
