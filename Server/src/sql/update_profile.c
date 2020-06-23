#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    if (!(strcmp(argv[0], "1"))) {
        cJSON_AddNumberToObject(data, "id", atoi(argv[1]));
        return false;
    }
    return true;
}

static int get_all(void *data, int argc, char **argv, char **cols) {
    cJSON_AddStringToObject(data, "first_name", argv[1]);
    cJSON_AddStringToObject(data, "second_name", argv[2]);
    cJSON_AddStringToObject(data, "email", argv[3]);
    cJSON_AddStringToObject(data, "status", argv[4]);
    return 0;
}

static void accept_authorization(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT * FROM users_profiles WHERE user_id = %i;",
             MX_VINT(jsn, "id"));

    rc = sqlite3_exec(db, query, get_all, jsn, &err);
    if (mx_check(rc, err, "accepted authorization") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_authorization);
    }
    free(query);
}

cJSON *mx_update_profile(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT * FROM users_profiles WHERE user_id = %i;",
    MX_VSTR(jsn, "login"), MX_VSTR(jsn, "hash"));
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    MX_SET_TYPE(jsn, success_authorization);
    if (mx_check(rc, err, "authorization") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_authorization);
    else
        accept_authorization(db, jsn);
    cJSON_DeleteItemFromObject(jsn, "login");
    cJSON_DeleteItemFromObject(jsn, "hash");
    free(query);
    return jsn;
}
