#include "server.h"

static int callback(void *data, int argc, char **argv, char **cols) {
    cJSON *contact = cJSON_CreateObject();
    const char *fields[] = {"uid", "login", "time", "content"};

    cJSON_AddNumberToObject(contact, fields[0], atoi(argv[0]));
    for (uint32_t i = 1; i < sizeof(fields) / sizeof(fields[0]); ++i)
        cJSON_AddStringToObject(contact, fields[i], argv[i]);

    cJSON_AddItemToArray(cJSON_GetObjectItem(data, "messages"), contact);
    return 0;
}

cJSON *mx_get_client_chat_messages(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT * FROM (SELECT m.user_id, u.login, m.send_time, "
             "m.content FROM messages AS m JOIN users AS u ON m.user_id = u.id"
             " WHERE m.chat_id = %i ORDER BY m.send_time DESC LIMIT 10) "
             "ORDER BY send_time ASC;", MX_VINT(jsn, "cid"));
    cJSON_AddArrayToObject(jsn, "messages");
    rc = sqlite3_exec(db, query, callback, jsn, &err);
    if (mx_check(rc, err, "get_client_chats_messages") != SQLITE_OK) {
        // ???????????????????????????????????????
    }
    else {
        MX_SET_TYPE(jsn, send_client_chat_messages);
    }
    free(query);
    return jsn;
}

// { "json_type": 20, "uid": 2, "cid": 1}
