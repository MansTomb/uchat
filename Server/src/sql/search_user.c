#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    cJSON *contact = cJSON_CreateObject();

    cJSON_AddNumberToObject(contact, cols[0], atoi(argv[0]));
    cJSON_AddStringToObject(contact, cols[1], argv[1]);
    cJSON_AddItemToArray(cJSON_GetObjectItem(data, "users"), contact);
    return 0;
}

cJSON *mx_search_user(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT id, login FROM users WHERE login LIKE '%%%s%%' "
            "LIMIT 15;", MX_VSTR(jsn, "login"));
    cJSON_AddArrayToObject(jsn, "users");
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    if (mx_check(rc, err, "find user login") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_search_user);
    }
    else {
        MX_SET_TYPE(jsn, success_search_user);
    }
    free(query);
    return jsn;
}
