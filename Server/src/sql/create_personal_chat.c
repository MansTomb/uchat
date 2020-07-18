#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "0") != 0;
}

static int get_id(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "cid", atoi(argv[0]));
    cJSON_AddNumberToObject(data, "role", 1);
    return 0;
}

static void create_new_chat(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO chats VALUES (NULL, 1, ''); SELECT "
            "last_insert_rowid(); INSERT INTO users_chats VALUES (%i, "
            "last_insert_rowid(), 1), (%i, (SELECT max(id) FROM chats), 1);",
            cJSON_GetObjectItem(jsn, "uid1")->valueint,
            cJSON_GetObjectItem(jsn, "uid2")->valueint);

    rc = sqlite3_exec(db, query, get_id, jsn, &err);
    if (mx_check(rc, err, "create personal chat") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_new_personal_chat);
    }
    free(query);
}

cJSON *mx_create_personal_chat(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(uc1.chat_id) FROM users_chats AS uc1 JOIN "
            "users_chats AS uc2 ON uc1.user_id = %i AND uc2.user_id = %i AND "
            "uc1.chat_id = uc2.chat_id JOIN chats AS c ON c.type = 1;",
            cJSON_GetObjectItem(jsn, "uid1")->valueint,
            cJSON_GetObjectItem(jsn, "uid2")->valueint);
    rc = sqlite3_exec(db, query, callback, jsn, &err);
    if (mx_check(rc, err, "create personal chat") != SQLITE_OK) {
        mx_get_present_chat(db, jsn);
    }
    else {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            success_new_personal_chat);
        create_new_chat(db, jsn);
    }
    free(query);
    return jsn;
}
