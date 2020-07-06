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

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (2, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (3, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (4, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (5, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (6, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (7, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (8, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (9, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (10, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (11, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (12, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (13, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (14, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (15, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (16, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (17, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (18, (SELECT max(id) FROM chats), 1);

INSERT INTO chats VALUES (NULL, 1, '');
INSERT INTO users_chats VALUES (1, last_insert_rowid(), 1);
INSERT INTO users_chats VALUES (19, (SELECT max(id) FROM chats), 1);
