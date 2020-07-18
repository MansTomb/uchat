#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "1") != 0;
}

static void update_groups(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "UPDATE contacts_lists SET group_id = 0 "
            "WHERE user_id = %i AND group_id = %i;",
            MX_VINT(jsn, "uid"), MX_VINT(jsn, "gid"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);

    if (mx_check(rc, err, "setting group to others") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_del_contact_group);
    }
    free(query);
}

static void del_group(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "DELETE FROM users_groups "
            "WHERE user_id = %i AND group_id = %i;",
            MX_VINT(jsn, "uid"), MX_VINT(jsn, "gid"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);

    if (mx_check(rc, err, "deleting group") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_del_contact_group);
    }
    else {
        update_groups(db, jsn);
    }
    free(query);
}

cJSON *mx_del_contact_group(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*) FROM users_groups "
            "WHERE user_id = %i AND group_id = %i;",
            MX_VINT(jsn, "uid"), MX_VINT(jsn, "gid"));
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    if (mx_check(rc, err, "del group") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_del_contact_group);
    }
    else {
        MX_SET_TYPE(jsn, success_del_contact_group);
        del_group(db, jsn);
    }
    free(query);
    return jsn;
}
