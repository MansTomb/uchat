#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "0");
}

static void accept_register(sqlite3 *db, cJSON *reg) {
    if (db && reg) {
        char *querry = NULL;
        char *err = NULL;
        int rc = 0;

        printf(":%s: :%s:\n", cJSON_GetObjectItem(reg, "login")->valuestring,
                cJSON_GetObjectItem(reg, "hash")->valuestring);

        asprintf(&querry, "INSERT INTO users VALUES (NULL, '%s', '%s');",
                cJSON_GetObjectItem(reg, "login")->valuestring,
                cJSON_GetObjectItem(reg, "hash")->valuestring);

        rc = sqlite3_exec(db, querry, NULL, NULL, &err);
        if (check(rc, err) != SQLITE_OK) {
            cJSON_SetIntValue(reg, MX_FAILED_REGISTER);
        }
        free(querry);
    }
}

cJSON *mx_registration(sqlite3 *db, cJSON *reg) {
    if (db && reg) {
        char *querry = NULL;
        char *err = NULL;
        int rc = 0;

        asprintf(&querry, "SELECT COUNT(*) FROM users WHERE login = '%s';",
                cJSON_GetObjectItem(reg, "login")->valuestring);
        printf("{%s}\n", querry);

        rc = sqlite3_exec(db, querry, callback, reg, &err);
        if (check(rc, err) != SQLITE_OK) {
            cJSON_SetIntValue(reg, MX_FAILED_REGISTER);
        }
        else {
            cJSON_SetIntValue(reg, MX_SUCCESS_REGISTER);
            accept_register(db, reg);
        }
        free(querry);
        return reg;
    }
    return NULL;
}
