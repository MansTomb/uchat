#include "server.h"

static int get_role(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "role", atoi(argv[0]));
    return 0;
}

cJSON *mx_send_message(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT role FROM users_chats WHERE user_id = %i AND "
            "chat_id = %i;", MX_VINT(jsn, "uid"), MX_VINT(jsn, "cid"));
    rc = sqlite3_exec(db, query, get_role, jsn, &err);

    if (mx_check(rc, err, "non-block user") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_send_message);
    else {
        if (MX_VINT(jsn, "role") == -1 
            || (MX_VINT(jsn, "cid") == 1 && MX_VINT(jsn, "uid") != 1))
            MX_SET_TYPE(jsn, failed_send_message);
        else {
           mx_insert_message_in_db(db, jsn);
        }
    }
    free(query);

    return jsn;
}
