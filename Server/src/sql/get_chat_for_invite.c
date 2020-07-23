#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    cJSON *user = cJSON_CreateObject();

    cJSON_AddNumberToObject(user, "uid", atoi(argv[0]));
    cJSON_AddStringToObject(user, "login", argv[1]);
    cJSON_AddItemToArray(cJSON_GetObjectItem(data, "users"), user);
    return 0;
}

static void get_users(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT u.id, u.login FROM users AS u JOIN users_chats AS"
            " uc ON uc.chat_id = %i AND u.id = uc.user_id AND uc.role > 0;",
            MX_VINT(jsn, "cid"));

    cJSON_AddArrayToObject(jsn, "users");
    rc = sqlite3_exec(db, query, callback, jsn, &err);
    if (mx_check(rc, err, "get users in chat") == SQLITE_OK) {
        MX_SET_TYPE(jsn, add_user_in_chat_return_chat);
    }
    free(query);
}

static int get_chat(void *data, int argc, char **argv, char **cols) {
    t_sql *sql = data;
    cJSON *chat = cJSON_CreateObject();

    cJSON_AddNumberToObject(chat, "cid", atoi(argv[0]));
    cJSON_AddNumberToObject(chat, "role", atoi(argv[1]));
    cJSON_AddNumberToObject(chat, "ctype", atoi(argv[2]));
    cJSON_AddStringToObject(chat, "cname", argv[3]);

    get_users(sql->db, chat);
    cJSON_AddItemToArray(cJSON_GetObjectItem(sql->jsn, "chat"), chat);
    return 0;
}

cJSON *mx_get_chat_for_invite(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;
    t_sql sql = {db, jsn};

    asprintf(&query, "SELECT uc.chat_id, uc.role, c.type, c.name "
             "FROM users_chats AS uc JOIN chats AS c ON uc.chat_id = c.id "
             "AND uc.user_id = %i AND uc.chat_id = %i ;",
             MX_VINT(jsn, "uid"), MX_VINT(jsn, "cid"));
    cJSON_AddArrayToObject(jsn, "chat");
    rc = sqlite3_exec(db, query, get_chat, &sql, &err);
    if (mx_check(rc, err, "get chats list") == SQLITE_OK) {
        MX_SET_TYPE(jsn, add_user_in_chat_return_chat);
    }
    free(query);
    return jsn;
}
