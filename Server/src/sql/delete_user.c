#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "1") != 0;
}

static void accept_deletion(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "DELETE FROM users WHERE id = %i;", MX_VINT(jsn, "uid"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);

    if (mx_check(rc, err, "delete user") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_delete_user);
    }
    else {
        MX_SET_TYPE(jsn, success_delete_user);
    }
    free(query);
}

cJSON *mx_delete_user(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*) FROM users WHERE id = %i AND "
            "login = '%s' AND hash = '%s';", MX_VINT(jsn, "uid"),
            MX_VSTR(jsn, "login"), MX_VSTR(jsn, "hash"));
    rc = sqlite3_exec(db, query, callback, NULL, &err);

    if (mx_check(rc, err, "delete user") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_delete_user);
    }
    else {
        accept_deletion(db, jsn);
    }
    cJSON_DeleteItemFromObject(jsn, "hash");
    free(query);
    return jsn;
}
