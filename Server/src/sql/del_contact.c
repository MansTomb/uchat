#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "1") != 0;
}

static void del_contact(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "DELETE FROM contacts_lists "
            "WHERE user_id = '%i' AND contact_id = '%i';",
            cJSON_GetObjectItem(jsn, "uid1")->valueint,
            cJSON_GetObjectItem(jsn, "uid2")->valueint);

    rc = sqlite3_exec(db, query, NULL, NULL, &err);
    if (mx_check(rc, err, "deleting contact") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_del_contact);
    }
    free(query);
}

cJSON *mx_del_contact(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*) FROM contacts_lists "
            "WHERE user_id = '%i' AND contact_id = '%i';",
            cJSON_GetObjectItem(jsn, "uid1")->valueint,
            cJSON_GetObjectItem(jsn, "uid2")->valueint);
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    if (mx_check(rc, err, "del contact") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_del_contact);
    }
    else {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            success_del_contact);
        del_contact(db, jsn);
    }
    free(query);
    return jsn;
}
