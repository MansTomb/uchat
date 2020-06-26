#include "server.h"

static int get_role(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "id", atoi(argv[0]));
    cJSON_AddNumberToObject(data, "role", atoi(argv[1]));
    return 0;
}

static void check_role(cJSON *jsn) {
    if (cJSON_GetObjectItem(jsn, "role")->valueint < 0) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_new_personal_chat);
    }
    else {
        char *query = NULL;
        char *err = NULL;
        int rc = 0;

        asprintf(&query, "UPDATE users_chats SET role = 1 WHERE chat_id = %i "
                "AND user_id = %i;", cJSON_GetObjectItem(jsn, "id")->valueint,
                cJSON_GetObjectItem(jsn, "uid1")->valueint);

        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "role"), 1);
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            success_new_personal_chat);
        mx_check(rc, err, "update role");
        free(query);
    }
}

void mx_get_present_chat(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT c.id, uc1.role FROM users_chats AS uc1 JOIN "
            "users_chats AS uc2 ON uc1.user_id = %i AND uc2.user_id = %i "
            "AND uc1.chat_id = uc2.chat_id JOIN chats AS c ON c.type = 1 "
            "AND uc1.chat_id = c.id;",
            cJSON_GetObjectItem(jsn, "uid1")->valueint,
            cJSON_GetObjectItem(jsn, "uid2")->valueint);

    rc = sqlite3_exec(db, query, get_role, jsn, &err);
    if (mx_check(rc, err, "get present chat") != SQLITE_OK) {
        cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
                            failed_new_personal_chat);
    }
    else {
        check_role(jsn);
    }
    free(query);
}
