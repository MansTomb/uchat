#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "1") != 0;
}

static void changing_password(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "UPDATE users SET hash='%s' "
             "WHERE login='%s' AND hash='%s';", MX_VSTR(jsn, "new_hash"),
             MX_VSTR(jsn, "login"), MX_VSTR(jsn, "hash"));

    rc = sqlite3_exec(db, query, NULL, NULL, &err);
    if (mx_check(rc, err, "inserting new password") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_change_password);
    }
    free(query);
}

cJSON *mx_change_password(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*) FROM users WHERE login = '%s' "
    "AND hash = '%s';", MX_VSTR(jsn, "login"), MX_VSTR(jsn, "hash"));
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    MX_SET_TYPE(jsn, success_change_password);
    if (mx_check(rc, err, "change password") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_change_password);
    else
        changing_password(db, jsn);
    cJSON_DeleteItemFromObject(jsn, "login");
    cJSON_DeleteItemFromObject(jsn, "hash");
    cJSON_DeleteItemFromObject(jsn, "new_hash");
    free(query);
    return jsn;
}
