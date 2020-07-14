#include "server.h"

static int create_users(sqlite3 *db) {
    char *query = MX_CREATE(users)
        MX_INT_PK(id)
        "login VARCHAR(32) NOT NULL UNIQUE, "
        "hash VARCHAR(64) NOT NULL); "
        MX_CREATE(users_profiles)
        MX_INT_PK(user_id)
        "first_name VARCHAR(64) DEFAULT '' NOT NULL, "
        "second_name VARCHAR(64) DEFAULT '' NOT NULL, "
        "email VARCHAR(64) DEFAULT '' NOT NULL, "
        "status VARCHAR(32) DEFAULT '' NOT NULL); "
        MX_CREATE(users_notify_settings)
        MX_INT_PK(user_id)
        "sound INTEGER NOT NULL, "
        "visual INTEGER NOT NULL, "
        "email INTEGER NOT NULL);";
    char *err = NULL;
    int rc = sqlite3_exec(db, query, NULL, NULL, &err);

    return mx_check(rc, err, "create users tables");
}

static int create_triggers(sqlite3 *db) {
    char *query = MX_TRIGGER(add_profile, INSERT)
        "users BEGIN "
        MX_INSERT(users_profiles, user_id) "(NEW.id); "
        "INSERT INTO users_notify_settings VALUES (NEW.id, 1, 1, 1); END; "
        MX_TRIGGER(del_profile, DELETE) "users BEGIN "
        MX_DEL_WH(users_profiles, user_id = OLD.id)
        MX_DEL_WH(users_notify_settings, user_id = OLD.id) "END;";
    char *err = NULL;
    int rc = sqlite3_exec(db, query, NULL, NULL, &err);

    return mx_check(rc, err, "create users triggers");
}

static int create_contacts(sqlite3 *db) {
    char *query = MX_CREATE(contacts_groups)
        MX_INT_PK(id)
        "name VARCHAR(64) NOT NULL UNIQUE); "
        MX_CREATE(users_groups)
        "user_id INTEGER NOT NULL, "
        "group_id INTEGER NOT NULL, "
        "PRIMARY KEY (user_id, group_id)); "
        MX_CREATE(contacts_lists)
        "user_id INTEGER NOT NULL, "
        "contact_id INTEGER NOT NULL, "
        "group_id INTEGER, "
        "PRIMARY KEY (user_id, contact_id), "
        "CHECK (user_id != contact_id));";
    char *err = NULL;
    int rc = sqlite3_exec(db, query, NULL, NULL, &err);

    return mx_check(rc, err, "create contacts tables");
}

static int create_chats(sqlite3 *db) {
    char *query = MX_CREATE(chats)
        MX_INT_PK(id)
        "type INTEGER NOT NULL, "
        "name VARCHAR(64) NOT NULL); "
        MX_CREATE(users_chats)
        "user_id INTEGER NOT NULL, "
        "chat_id INTEGER NOT NULL, "
        "role INTEGER DEFAULT 1 NOT NULL, "
        "PRIMARY KEY (user_id, chat_id));"
        MX_CREATE(messages)
        MX_INT_PK(id)
        "user_id INTEGER NOT NULL, "
        "chat_id INTEGER NOT NULL, "
        "type INTEGER NOT NULL, "
        "send_time CHAR(19) NOT NULL, "
        "content VARCHAR(64) NOT NULL);";
    char *err = NULL;
    int rc = sqlite3_exec(db, query, NULL, NULL, &err);

    return mx_check(rc, err, "create chats tables");
}

int mx_create_db(sqlite3 *db) {
    int rc = 0;

    if ((rc = create_users(db)) == SQLITE_OK) {
        if ((rc = create_triggers(db)) == SQLITE_OK) {
            if ((rc = create_contacts(db)) == SQLITE_OK) {
                rc = create_chats(db);
            }
        }
    }
    return rc;
}
