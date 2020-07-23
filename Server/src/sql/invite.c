#include "server.h"

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
    int count = 0;
    int *new_uid;
    int i;

    for (i = 0; uid[i] != 0; ++i)
        count++;
    new_uid = malloc(count * sizeof(int));
    for (i = 0; i < count; ++i)
        new_uid[i] = uid[i];

    cJSON_AddItemToObject(jsn, "clients_id", cJSON_CreateIntArray(new_uid, count));

    free(uid);
    free(new_uid);
}

static void get_all_users(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;
    int *uid = malloc(MAX_CLIENTS * sizeof(int));

    bzero(uid, MAX_CLIENTS);
    asprintf(&query, "SELECT user_id FROM users_chats WHERE chat_id = %i "
            "AND role > 0;", MX_VINT(jsn, "cid"));

    rc = sqlite3_exec(db, query, get_id, uid, &err);
    if (mx_check(rc, err, "get all users") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_add_user_in_chat);
    else
        get_arr_users(db, jsn, uid);
    free(query);
}

static int callback(void *data, int argc, char **argv, char **cols) {
    return strcmp(argv[0], "0") != 0;
}

void mx_insert_invite(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT count(*) FROM users_chats WHERE user_id = %i AND "
             "chat_id = %i;", MX_VINT(jsn, "uid"), MX_VINT(jsn, "cid"));
    rc = sqlite3_exec(db, query, callback, jsn, &err);
    if (mx_check(rc, err, "invite") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_add_user_in_chat);
    else {
        free(query);
        asprintf(&query, "INSERT INTO users_chats VALUES (%i, %i, 1);",
                 MX_VINT(jsn, "uid"), MX_VINT(jsn, "cid"));
        rc = sqlite3_exec(db, query, NULL, NULL, &err);
        if (mx_check(rc, err, "invite") != SQLITE_OK)
            MX_SET_TYPE(jsn, failed_add_user_in_chat);
        else
            get_all_users(db, jsn);
    }
    free(query);
}
