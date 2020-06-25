#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "1") != 0;
}

static void update_profile(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "UPDATE users_profiles SET first_name='%s', "
             "second_name='%s', email='%s', status='%s' WHERE user_id=%i;",
             MX_VSTR(jsn, "fname"), MX_VSTR(jsn, "sname"),
             MX_VSTR(jsn, "email"), MX_VSTR(jsn, "status"), MX_VINT(jsn, "uid"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);
    if (mx_check(rc, err, "updating1_profile") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_authorization);
    }
    free(query);

    asprintf(&query, "UPDATE users_notify_settings SET sound=%i, visual=%i, "
             "email=%i  WHERE user_id=%i;", MX_VINT(jsn, "snot"),
             MX_VINT(jsn, "vnot"), MX_VINT(jsn, "enot"), MX_VINT(jsn, "uid"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);
    if (mx_check(rc, err, "updating2_profile") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_authorization);
    }
    free(query);
}

cJSON *mx_update_profile(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*) FROM users_profiles WHERE user_id = %i;",
             MX_VINT(jsn, "uid"));

    rc = sqlite3_exec(db, query, callback, jsn, &err);

    MX_SET_TYPE(jsn, success_update_profile);
    if (mx_check(rc, err, "update_profile") != SQLITE_OK) {
        // MX_SET_TYPE(jsn, failed_authorization); ?????????
    }
    else
        update_profile(db, jsn);
    free(query);
    return jsn;
}
