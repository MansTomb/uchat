#include "server.h"

// static int callback(void *data, int argc, char **argv, char **cols) {
//     return 0;
// }

static int get_id(void *data, int argc, char **argv, char **cols) {
    // cJSON_AddNumberToObject(data, "id", atoi(argv[0]));
    printf("user id = %d\n", atoi(argv[0]));
    return 0;
}

static void get_all_users(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT user_id FROM users_chats WHERE chat_id = '%i' AND user_id != '%i';",
            cJSON_GetObjectItem(jsn, "chat_id")->valueint,
            cJSON_GetObjectItem(jsn, "uid")->valueint);

    rc = sqlite3_exec(db, query, get_id, jsn, &err);
    if (mx_check(rc, err, "get all users") != SQLITE_OK) {
        // cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
        //                     failed_change_password);
    }
    free(query);
}

cJSON *mx_send_message(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO messages VALUES (NULL, '%i', '%i', '%i', "
            "datetime('now', 'localtime'), '%s');",
            cJSON_GetObjectItem(jsn, "uid")->valueint,
            cJSON_GetObjectItem(jsn, "chat_id")->valueint,
            cJSON_GetObjectItem(jsn, "type")->valueint,
            cJSON_GetObjectItem(jsn, "content")->valuestring);
    rc = sqlite3_exec(db, query, NULL, jsn, &err);

    if (mx_check(rc, err, "send message") != SQLITE_OK) {
        // cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
        //                     failed_change_password);
    }
    else {
        // cJSON_SetNumberValue(cJSON_GetObjectItem(jsn, "json_type"),
        //                     success_change_password);
        get_all_users(db, jsn);
    }
    free(query);
    return jsn;
}
