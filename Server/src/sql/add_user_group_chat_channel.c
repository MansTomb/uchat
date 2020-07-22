#include "server.h"

cJSON *mx_add_user_group_chat_channel(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO users_chats VALUES (%i, %i, 1);",
            MX_VINT(jsn, "uid"), MX_VSTR(jsn, "cid"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);

    if (mx_check(rc, err, "add user to group chat / channel") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_add_user_in_chat);
    }
    else {
        MX_SET_TYPE(jsn, success_add_user_in_chat);
    }
    free(query);
    return jsn;
}
