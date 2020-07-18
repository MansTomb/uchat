-- .headers on
-- .mode column

INSERT INTO users VALUES
    (NULL, 'abalabin', 'qwerty'),
    (NULL, 'oafanasiev', 'asdfgh'),
    (NULL, 'trohalska', 'zxcvbn'),
    (NULL, 'yburienkov', 'lpmkoj'),
    (NULL, 'vasya228', 'lpmkoj'),
    (NULL, 'uberangibator', 'asdaad'),
    (NULL, 'pavuk', 'sgdgsd'),
    (NULL, 'neLyud', 'sdgsdg'),
    (NULL, 'tvoibatya', 'sdgsdg'),
    (NULL, 'glinomes', 'dgsgds'),
    (NULL, 'kozaniimewok', 'gsdgds'),
    (NULL, 'leatherman', 'dsgsdg'),
    (NULL, 'billy', 'sdgsdg'),
    (NULL, 'baran', 'gsgsgg'),
    (NULL, 'gandam', 'nhtfhg'),
    (NULL, 'Petrovich', 'nsdfsd'),
    (NULL, 'Uwativatel', 'nfdfgf'),
    (NULL, 'ineedhelp', 'ntrhtr'),
    (NULL, 'tootoo', 'hhtrhr');

INSERT INTO contacts_lists (user_id, contact_id) VALUES
    (1, 2),
    (1, 3),
    (1, 4),
    (1, 5),
    (1, 6),
    (1, 7),
    (1, 8),
    (1, 9),
    (1, 10),
    (1, 11),
    (1, 12),
    (1, 13),
    (1, 14),
    (1, 15),
    (1, 16),
    (1, 17),
    (1, 18),
    (1, 19);

INSERT INTO contacts_groups VALUES
    (NULL, 'friends'),
    (NULL, 'work'),
    (NULL, 'family'),
    (NULL, 'sluts'),
    (NULL, 'whores'),
    (NULL, 'milfs');

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (2, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (3, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (4, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (5, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (6, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (7, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (8, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (9, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (10, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (11, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (12, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (13, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (14, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (15, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (16, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (17, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (18, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1), (19, (SELECT max(id) FROM chats), 1);
