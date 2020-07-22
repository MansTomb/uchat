#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    cJSON *chat = cJSON_CreateObject();
    cJSON_AddNumberToObject(chat, "cid", atoi(argv[0]));
    cJSON_AddNumberToObject(chat, "role", atoi(argv[1]));
    cJSON_AddNumberToObject(chat, "ctype", atoi(argv[2]));
    cJSON_AddStringToObject(chat, "cname", argv[3]);
    cJSON_AddItemToArray(cJSON_GetObjectItem(data, "chats"), chat);
    return 0;
}

cJSON *mx_get_clients_chats(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int uid = MX_VINT(jsn, "uid");
    int rc = 0;

    asprintf(&query, "SELECT uc.chat_id, uc.role, c.type, CASE WHEN c.type = 1"
            " THEN (SELECT u.login FROM users AS u JOIN users_chats AS uc ON "
            "uc.chat_id = c.id AND uc.user_id != %i AND uc.user_id = u.id) "
            "ELSE c.name END name FROM users_chats AS uc JOIN chats AS c ON uc"
            ".chat_id = c.id AND uc.user_id = %i AND uc.role > 0;", uid, uid);

    cJSON_AddArrayToObject(jsn, "chats");
    rc = sqlite3_exec(db, query, callback, jsn, &err);
    if (mx_check(rc, err, "get chats list") != SQLITE_OK) {
        // ???????????????????????????????????????
    }
    else {
        MX_SET_TYPE(jsn, send_client_chats);
    }
    free(query);
    return jsn;
}
