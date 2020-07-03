#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    if (!(strcmp(argv[0], "1"))) {
        cJSON_AddNumberToObject(data, "coid", atoi(argv[1]));
        return false;
    }
    return true;
}

static void add_new_contact(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO contacts_lists VALUES (%i, %i, NULL);",
            MX_VINT(jsn, "uid"), MX_VINT(jsn, "coid"));

    rc = sqlite3_exec(db, query, NULL, NULL, &err);
    if (mx_check(rc, err, "adding new contact") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_add_new_contact);
    }
    free(query);
}

cJSON *mx_add_new_contact(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    // should take coid = contact id
    asprintf(&query, "SELECT count(*), id FROM users WHERE login = '%s';",
            MX_VSTR(jsn, "friend_login"));
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    if (mx_check(rc, err, "add new contact") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_add_new_contact);
    }
    else {
        MX_SET_TYPE(jsn, success_add_new_contact);
        add_new_contact(db, jsn);
    }
    free(query);
    return jsn;
}
