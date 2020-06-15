#include "server.h"

static int check(int rc, char *err) {
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err);
        sqlite3_free(err);
    }
    return rc;
}

static int create_db(sqlite3 *db) {
    char *err = NULL;
    char *query3 = MX_CREATE(contact_groups) MX_INT_PK(id)
    "name VARCHAR(64) NOT NULL UNIQUE); " MX_CREATE(contact_lists)
    "user_id INTEGER NOT NULL, contact_id INTEGER NOT NULL, group_id INTEGER, "
    "PRIMARY KEY (user_id, contact_id));" MX_CREATE(chats) MX_INT_PK(id)
    "type INTEGER NOT NULL, name VARCHAR(64) NOT NULL);";
    char *query4 = MX_CREATE(user_chats) "user_id INTEGER NOT NULL, "
    "chat_id INTEGER NOT NULL, role INTEGER DEFAULT 1, "
    "PRIMARY KEY (user_id, chat_id));" MX_CREATE(messages)
    MX_INT_PK(id) "user_id INTEGER NOT NULL, chat_id INTEGER NOT NULL, "
    "type INTEGER NOT NULL, send_time CHAR(19) NOT NULL, "
    "content VARCHAR(64) NOT NULL);" MX_CREATE(block_lists) 
    "chat_id INTEGER NOT NULL, banned_id INTEGER NOT NULL, "
    "PRIMARY KEY (chat_id, banned_id));";
    int rc = sqlite3_exec(db, query3, NULL, NULL, &err);

    if (check(rc, err) == SQLITE_OK)
        rc = sqlite3_exec(db, query4, NULL, NULL, &err);
    return check(rc, err);
}

int mx_create_db(sqlite3 *db) {
    char *err = NULL;
    char *query1 = MX_CREATE(users) MX_INT_PK(id) "login VARCHAR(32) NOT NULL "
    "UNIQUE, salt VARCHAR(64) NOT NULL UNIQUE, hash VARCHAR(64) NOT NULL); "
    MX_CREATE(users_profiles) "user_id INTEGER PRIMARY KEY NOT NULL, "
    "first_name VARCHAR(64), second_name VARCHAR(64), status VARCHAR(32), "
    "register_time CHAR(19));";
    char *query2 = MX_TRIGGER(add_profile, INSERT) "users BEGIN "
    MX_INSERT(users_profiles, user_id, register_time)
    "(NEW.id, datetime('now', 'localtime')); END; "
    MX_TRIGGER(del_profile, DELETE) "users BEGIN "
    MX_DEL_WH(users_profiles, user_id = OLD.id) "END;";
    int rc = sqlite3_exec(db, query1, NULL, NULL, &err);

    if (check(rc, err) == SQLITE_OK) {
        rc = sqlite3_exec(db, query2, NULL, NULL, &err);
        if (check(rc, err) == SQLITE_OK)
            rc = create_db(db);
    }
    return rc;
}
