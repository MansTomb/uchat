#include "server.h"

static int get_count(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "0") == 0;
}

static void update_role(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "UPDATE users_chats SET role = 1 WHERE chat_id = %i AND "
            "user_id = %i;", MX_VINT(jsn, "cid"), MX_VINT(jsn, "uid"));

    MX_SET_TYPE(jsn, success_add_user_in_chat);
    mx_check(rc, err, "update role");
    free(query);
}

static void check_role(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(role) FROM users_chats WHERE user_id = %i "
            "AND chat_id = %i;", MX_VINT(jsn, "uid"), MX_VINT(jsn, "cid"));
    rc = sqlite3_exec(db, query, get_count, NULL, &err);

    if (mx_check(rc, err, "get present group chat / channel") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_add_user_in_chat);
    }
    else {
        update_role(db, jsn);
    }
    free(query);
}

cJSON *mx_add_user_group_chat_channel(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO users_chats VALUES (%i, %i, 1);",
            MX_VINT(jsn, "uid"), MX_VINT(jsn, "cid"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);

    if (mx_check(rc, err, "add user to group chat / channel") != SQLITE_OK) {
        check_role(db, jsn);
    }
    else {
        MX_SET_TYPE(jsn, success_add_user_in_chat);
    }
    free(query);
    return jsn;
}
