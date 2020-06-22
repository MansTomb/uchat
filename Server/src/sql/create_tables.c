#include "server.h"

static int create_db(sqlite3 *db) {
    char *query3 = MX_CREATE(contacts_groups) MX_INT_PK(id)
    "name VARCHAR(64) NOT NULL UNIQUE); " MX_CREATE(contacts_lists)
    "user_id INTEGER NOT NULL, contact_id INTEGER NOT NULL, group_id INTEGER, "
    "PRIMARY KEY (user_id, contact_id), CHECK (user_id != contact_id));"
    MX_CREATE(chats) MX_INT_PK(id)
    "type INTEGER NOT NULL, name VARCHAR(64) NOT NULL);";
    char *query4 = MX_CREATE(users_chats) "user_id INTEGER NOT NULL, "
    "chat_id INTEGER NOT NULL, role INTEGER DEFAULT 1 NOT NULL, "
    "PRIMARY KEY (user_id, chat_id));" MX_CREATE(messages)
    MX_INT_PK(id) "user_id INTEGER NOT NULL, chat_id INTEGER NOT NULL, "
    "type INTEGER NOT NULL, send_time CHAR(19) NOT NULL, "
    "content VARCHAR(64) NOT NULL);";
    char *err = NULL;
    int rc = sqlite3_exec(db, query3, NULL, NULL, &err);

    if (mx_check(rc, err, "create query 3") == SQLITE_OK)
        rc = sqlite3_exec(db, query4, NULL, NULL, &err);
    return mx_check(rc, err, "create query 4");
}

int mx_create_db(sqlite3 *db) {
    char *query1 = MX_CREATE(users) MX_INT_PK(id) "login VARCHAR(32) NOT NULL "
    "UNIQUE, hash VARCHAR(64) NOT NULL); " MX_CREATE(users_profiles)
    "user_id INTEGER PRIMARY KEY NOT NULL, first_name VARCHAR(64), "
    "second_name VARCHAR(64), email VARCHAR(64), status VARCHAR(32));"
    MX_CREATE(users_notify_settings) "user_id INTEGER PRIMARY KEY NOT NULL, "
    "sound INTEGER NOT NULL, visual INTEGER NOT NULL,email INTEGER NOT NULL);";
    char *query2 = MX_TRIGGER(add_profile, INSERT) "users BEGIN " MX_INSERT(
    users_profiles, user_id) "(NEW.id); INSERT INTO users_notify_settings "
    "VALUES (NEW.id, 1, 1, 0); END; " MX_TRIGGER(del_profile, DELETE)
    "users BEGIN " MX_DEL_WH(users_profiles, user_id = OLD.id) 
    MX_DEL_WH(users_notify_settings, user_id = OLD.id) "END;";
    char *err = NULL;
    int rc = sqlite3_exec(db, query1, NULL, NULL, &err);

    if (mx_check(rc, err, "create query 1") == SQLITE_OK) {
        if (mx_check((rc = sqlite3_exec(db, query2, NULL, NULL, &err)), err,
                                    "create query 2") == 0)
            rc = create_db(db);
    }
    return rc;
}
