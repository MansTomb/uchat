#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    if (!(strcmp(argv[0], "1"))) {
        cJSON_AddNumberToObject(data, "uid", atoi(argv[1]));
        return 0;
    }
    return 1;
}

static int get_all(void *data, int argc, char **argv, char **cols) {
    const char *strs[] = {"fname", "sname", "email", "status"};
    const char *ints[] = {"snotify", "vnotify", "enotify"};
    const size_t size = sizeof(strs) / sizeof(strs[0]);

    for (size_t i = 0; i < size; ++i)
        cJSON_AddStringToObject(data, strs[i], argv[i]);
    for (size_t i = 0; i < sizeof(ints) / sizeof(ints[0]); ++i)
        cJSON_AddNumberToObject(data, strs[i], atoi(argv[i + size]));

    return 0;
}

static void accept_authorization(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT up.first_name, up.second_name, up.email, "
            "up.status, uns.sound, uns.visual, uns.email FROM users_profiles "
            "AS up JOIN users_notify_settings AS uns ON up.user_id = %i AND "
            "up.user_id = uns.user_id;", MX_VINT(jsn, "uid"));

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
    cJSON_DeleteItemFromObject(jsn, "hash");
    free(query);
    return jsn;
}
