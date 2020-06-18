#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "0") != 0;
}

static int get_id(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "id", atoi(argv[0]));
    return 0;
}

static void accept_register(sqlite3 *db, cJSON *reg) {
    char *querry = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&querry, "INSERT INTO users VALUES (NULL, '%s', '%s'); "
            "SELECT last_insert_rowid();",
            cJSON_GetObjectItem(reg, "login")->valuestring,
            cJSON_GetObjectItem(reg, "hash")->valuestring);

    rc = sqlite3_exec(db, querry, get_id, reg, &err);
    if (check(rc, err, "accepted registration") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(reg, "json_type"),
                            failed_register);
    }
    free(querry);
}

cJSON *mx_registration(sqlite3 *db, cJSON *reg) {
    char *querry = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&querry, "SELECT COUNT(*) FROM users WHERE login = '%s';",
            cJSON_GetObjectItem(reg, "login")->valuestring);
    rc = sqlite3_exec(db, querry, callback, reg, &err);

    if (check(rc, err, "registration") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(reg, "json_type"),
                            failed_register);
    }
    else {
        cJSON_SetNumberValue(cJSON_GetObjectItem(reg, "json_type"),
                            success_register);
        accept_register(db, reg);
    }
    free(querry);
    return reg;
}
