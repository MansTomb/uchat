#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "1") != 0;
}

static int get_id(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "id", atoi(argv[0]));
    return 0;
}

static void accept_authorization(sqlite3 *db, cJSON *jsn) {
    char *querry = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&querry, "SELECT id FROM users WHERE login='%s' AND hash='%s';",
            cJSON_GetObjectItem(jsn, "login")->valuestring,
            cJSON_GetObjectItem(jsn, "hash")->valuestring);

    rc = sqlite3_exec(db, querry, get_id, jsn, &err);
    if (check(rc, err, "accepted authorization") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_authorization);
    }
    free(querry);
}

cJSON *mx_authorization(sqlite3 *db, cJSON *jsn) {
    char *querry = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&querry, "SELECT count(*) FROM users WHERE login = '%s' "
    "AND hash = '%s';", cJSON_GetObjectItem(jsn, "login")->valuestring,
    cJSON_GetObjectItem(jsn, "hash")->valuestring);
    rc = sqlite3_exec(db, querry, callback, jsn, &err);

    if (check(rc, err, "authorization") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_authorization);
    }
    else {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            success_authorization);
        accept_authorization(db, jsn);
    }
    free(querry);
    return jsn;
}
