#include "server.h"

static int get_email(void *data, int argc, char **argv, char **cols) {
    cJSON_AddStringToObject(data, "email", argv[0]);
    return 0;
}

static int get_id(void *data, int argc, char **argv, char **cols) {
    int *cli = data;

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (cli[i] == 0) {
            cli[i] = atoi(argv[0]);
            break;
        }
    }
    return 0;
}

static void get_arr_users(sqlite3 *db, cJSON *jsn, int *uid) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;
    int count = 0;

    for (int i = 0; uid[i] != 0; ++i)
        count++;
    int *new_uid = malloc(count * sizeof(int));
    for (int i = 0; i < count; ++i)
        new_uid[i] = uid[i];

    cJSON_AddItemToObject(jsn, "clients_id", cJSON_CreateIntArray(new_uid, count));

    free(uid);
    free(new_uid);
    free(query);
}

static void get_all_users(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;
    int *uid = malloc(MAX_CLIENTS * sizeof(int));

    bzero(uid, MAX_CLIENTS);
    asprintf(&query, "SELECT user_id FROM users_chats WHERE chat_id == %i "
             "AND user_id != %i AND role > 0;",
             MX_VINT(jsn, "chat_id"), MX_VINT(jsn, "uid"));

    rc = sqlite3_exec(db, query, get_id, uid, &err);
    if (mx_check(rc, err, "get all users") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_send_message);
    else
        get_arr_users(db, jsn, uid);
    free(query);
}

cJSON *mx_send_message(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO messages VALUES (NULL, %i, %i, %i, "
            "datetime('now', 'localtime'), '%s');",
            MX_VINT(jsn, "uid"), MX_VINT(jsn, "chat_id"),
            MX_VINT(jsn, "type"), MX_VSTR(jsn, "content"));
    rc = sqlite3_exec(db, query, NULL, NULL, &err);

    if (mx_check(rc, err, "send message") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_send_message);
    else
        get_all_users(db, jsn);
    free(query);
    return jsn;
}
