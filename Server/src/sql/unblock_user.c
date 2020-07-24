#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "role", 1);
    cJSON_AddNumberToObject(data, "ctype", atoi(argv[0]));

    return 0;
}

cJSON *mx_unblock_user(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "UPDATE users_chats SET role = 1 WHERE user_id = %i AND "
             "chat_id = %i; SELECT type FROM chats WHERE id = %i;",
             MX_VINT(jsn, "uid"), MX_VINT(jsn, "cid"), MX_VINT(jsn, "cid"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);

    if (mx_check(rc, err, "unblock user") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_unblock_user);
    }
    else {
        MX_SET_TYPE(jsn, success_unblock_user);
    }
    free(query);
    return jsn;
}
