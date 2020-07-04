#include "server.h"

cJSON *mx_create_group_chat_channel(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO chats VALUES (NULL, %i, '%s'); INSERT INTO "
            "users_chats VALUES (%i, last_insert_rowid(), 2);",
            MX_VINT(jsn, "ctype"), MX_VSTR(jsn, "cname"), MX_VINT(jsn, "uid"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);

    if (mx_check(rc, err, "create group chat / channel") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_new_group_chat_channel);
    }
    else {
        MX_SET_TYPE(jsn, success_new_group_chat_channel);
    }
    free(query);
    return jsn;
}
