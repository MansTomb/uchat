#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    if (!(strcmp(argv[0], "1"))) {
        cJSON_AddNumberToObject(data, "id", atoi(argv[1]));
        return 0;
    }
    return 1;
}

static int get_all(void *data, int argc, char **argv, char **cols) {
    cJSON_AddStringToObject(data, "first_name", argv[1]);
    cJSON_AddStringToObject(data, "second_name", argv[2]);
    cJSON_AddStringToObject(data, "email", argv[3]);
    cJSON_AddStringToObject(data, "status", argv[4]);
    cJSON_AddStringToObject(data, "sound_notify", argv[6]);
    cJSON_AddStringToObject(data, "visual_notify", argv[7]);
    return 0;
}

static void accept_authorization(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT * FROM users_profiles AS up JOIN users_notify_set"
            "tings uns ON up.user_id = %i AND uns.user_id = up.user_id;",
            MX_VINT(jsn, "id"));

    rc = sqlite3_exec(db, query, get_all, jsn, &err);
    if (mx_check(rc, err, "accepted authorization") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_authorization);
    }
    free(query);
}

cJSON *mx_authorization(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*), id FROM users WHERE login = '%s' "
            "AND hash = '%s';", MX_VSTR(jsn, "login"), MX_VSTR(jsn, "hash"));
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    MX_SET_TYPE(jsn, success_authorization);
    if (mx_check(rc, err, "authorization") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_authorization);
    else
        accept_authorization(db, jsn);
    // if (!cJSON_IsNull(cJSON_GetObjectItem(jsn, "first_name")))
    //     printf("first ----- NULL");
    // if (!cJSON_IsNull(cJSON_GetObjectItem(jsn, "email")))
    //     printf("email ----- not");
    cJSON_DeleteItemFromObject(jsn, "hash");
    free(query);
    return jsn;
}
