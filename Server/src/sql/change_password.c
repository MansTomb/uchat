#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "1") != 0;
}

static int get_id(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "id", atoi(argv[0]));
    return 0;
}

static void changing_password(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "UPDATE users SET hash='%s' WHERE login='%s' AND hash='%s';",
            cJSON_GetObjectItem(jsn, "new_hash")->valuestring,
            cJSON_GetObjectItem(jsn, "login")->valuestring,
            cJSON_GetObjectItem(jsn, "hash")->valuestring);

    rc = sqlite3_exec(db, query, get_id, jsn, &err);
    if (mx_check(rc, err, "inserting new password") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_change_password);
    }
    free(query);
}

cJSON *mx_change_password(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*) FROM users WHERE login = '%s' "
    "AND hash = '%s';", cJSON_GetObjectItem(jsn, "login")->valuestring,
    cJSON_GetObjectItem(jsn, "hash")->valuestring);
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    if (mx_check(rc, err, "change password") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_change_password);
    }
    else {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            success_change_password);
        changing_password(db, jsn);
    }
    free(query);
    return jsn;
}
