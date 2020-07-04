#include "server.h"

cJSON *mx_add_new_contact(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO contacts_lists VALUES (%i, %i, NULL);",
            MX_VINT(jsn, "uid"), MX_VINT(jsn, "coid"));

    rc = sqlite3_exec(db, query, NULL, NULL, &err);
    if (mx_check(rc, err, "adding new contact") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_add_new_contact);
    }
    else {
        MX_SET_TYPE(jsn, success_add_new_contact);
    }
    free(query);
    return jsn;
}
