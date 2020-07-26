#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    cJSON_AddStringToObject(data, "login", argv[0]);

    return 0;
}

cJSON *mx_leave_chat(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    mx_get_all_users_in_chat(db, jsn, MX_VINT(jsn, "cid"));
    asprintf(&query, "UPDATE users_chats SET role = 0 WHERE user_id = %i AND "
            "chat_id = %i; SELECT login FROM users WHERE id = %i",
            MX_VINT(jsn, "uid"), MX_VINT(jsn, "cid"), MX_VINT(jsn, "uid"));
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    if (mx_check(rc, err, "leave chat") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_leave_chat);
    }
    else {
        MX_SET_TYPE(jsn, success_leave_chat);
    }
    free(query);
    return jsn;
}
