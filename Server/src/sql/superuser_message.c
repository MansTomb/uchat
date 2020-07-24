#include "server.h"

static int get_mid(void *data, int argc, char **argv, char **cols) {
    // cJSON_AddStringToObject(data, "login", argv[0]);
    cJSON_AddStringToObject(data, "login", "Master of Evil");
    cJSON_AddNumberToObject(data, "mid", atoi(argv[1]));
    cJSON_AddStringToObject(data, "time", argv[2]);
    cJSON_AddNumberToObject(data, "type", atoi(argv[3]));
    cJSON_AddNumberToObject(data, "role", 2);

    return 0;
}

cJSON *mx_superuser_message(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "INSERT INTO messages VALUES (NULL, 1, 1, 1, "
            "datetime('now', 'localtime'), '%s'); "
            "SELECT u.login, m.id, m.send_time, m.type "
            "FROM messages AS m JOIN users AS u ON u.id = m.user_id "
            "AND m.id = last_insert_rowid();", MX_VSTR(jsn, "content"));
    rc = sqlite3_exec(db, query, get_mid, jsn, &err);

    if (mx_check(rc, err, "send message") != SQLITE_OK)
        MX_SET_TYPE(jsn, failed_send_message);
    else
        mx_get_all_users_in_chat(db, jsn, 1);
    free(query);
    return jsn;
}
