#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "0") != 0;
}

static int get_id(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "uid", atoi(argv[0]));
    return 0;
}

static void add_to_super_chanel(sqlite3 *db, cJSON *jsn) {
    char *query = "INSERT INTO users_chats VALUES (last_insert_rowid(), 1,1);";
    char *err = NULL;
    int rc = sqlite3_exec(db, query, NULL, NULL, &err);

    mx_check(rc, err, "add to super-chat");
}

static void accept_register(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO users VALUES (NULL, '%s', '%s'); SELECT last"
            "_insert_rowid();", MX_VSTR(jsn, "login"), MX_VSTR(jsn, "hash"));

    rc = sqlite3_exec(db, query, get_id, jsn, &err);
    if (mx_check(rc, err, "accepted registration") != SQLITE_OK) {
        MX_SET_TYPE(jsn, failed_register);
    }
    else {
        MX_SET_TYPE(jsn, success_register);
    }
    free(query);
}

cJSON *mx_registration(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*) FROM users WHERE login = '%s';",
            MX_VSTR(jsn, "login"));
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    if (mx_check(rc, err, "registration") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_register);
    else {
        accept_register(db, jsn);
        add_to_super_chanel(db, jsn);
    }
    cJSON_DeleteItemFromObject(jsn, "login");
    cJSON_DeleteItemFromObject(jsn, "hash");
    free(query);
    return jsn;
}
