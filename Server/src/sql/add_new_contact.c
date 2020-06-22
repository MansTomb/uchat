#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    if (!(strcmp(argv[0], "1"))) {
        cJSON_AddNumberToObject(data, "contact_id", atoi(argv[1]));
        return false;
    }
    return true;
}

// static int get_id(void *data, int argc, char **argv, char **cols) {
//     cJSON_AddNumberToObject(data, "id", atoi(argv[0]));
//     return 0;
// }

static void add_new_contact(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO contacts_lists VALUES ('%i', '%i', NULL);",
            cJSON_GetObjectItem(jsn, "uid")->valueint,
            cJSON_GetObjectItem(jsn, "contact_id")->valueint);

    rc = sqlite3_exec(db, query, NULL, NULL, &err);
    if (mx_check(rc, err, "adding new contact") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_add_new_contact);
    }
    free(query);
}

cJSON *mx_add_new_contact(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*), id FROM users WHERE login = '%s';",
            cJSON_GetObjectItem(jsn, "friend_login")->valuestring);
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    if (mx_check(rc, err, "add new contact") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_add_new_contact);
    }
    else {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            success_add_new_contact);
        add_new_contact(db, jsn);
    }
    free(query);
    return jsn;
}
