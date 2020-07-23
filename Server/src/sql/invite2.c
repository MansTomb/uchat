#include "server.h"

static int get_id_by_login(void *data, int argc, char **argv, char **cols) {
    if (!(strcmp(argv[0], "1"))) {
        cJSON_AddNumberToObject(data, "uid", atoi(argv[1]));
        return 0;
    }
    return 1;
}

cJSON *mx_invite(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*), id FROM users WHERE login = '%s';",
             MX_VSTR(jsn, "login"));
    rc = sqlite3_exec(db, query, get_id_by_login, jsn, &err);
    if (mx_check(rc, err, "invite") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_add_user_in_chat);
    else {
        MX_SET_TYPE(jsn, success_add_user_in_chat);
        mx_insert_invite(db, jsn);
    }

    free(query);
    return jsn;
}
