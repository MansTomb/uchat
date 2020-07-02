#include "server.h"

static int get_email(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "email_set", atoi(argv[0]));
    cJSON_AddStringToObject(data, "email", argv[1]);
    return 0;
}

static void get_notify_and_email(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;
    char *email;

    asprintf(&query, "SELECT uns.email, up.email "
            "FROM users_notify_settings AS uns JOIN users_profiles AS up "
            "ON uns.user_id = up.user_id WHERE up.user_id = %i;",
            (int)cJSON_GetNumberValue(cJSON_GetArrayItem(
                    cJSON_GetObjectItem(jsn, "clients_id"), 0)));

    rc = sqlite3_exec(db, query, get_email, jsn, &err);
    if (mx_check(rc, err, "get_notify_and_email") != SQLITE_OK)
        return;
    else {
        if (MX_VINT(jsn, "email_set") == 1)
            if ((email = MX_VSTR(jsn, "email")) && email[0])
                mx_message_on_mail(MX_VSTR(jsn, "email"), MX_EMAIL_PATH);
    }
    free(query);
}

static int callback(void *data, int argc, char **argv, char **cols) {
    cJSON_AddNumberToObject(data, "chat_type", atoi(argv[0]));
    return 0;
}

cJSON *mx_if_message_on_mail(sqlite3 *db, cJSON *jsn) {
    char *query = NULL;
    char *err = NULL;
    int rc = 0;

    asprintf(&query, "SELECT type FROM chats WHERE id = %i",
            MX_VINT(jsn, "cid"));
    rc = sqlite3_exec(db, query, callback, jsn, &err);

    if (mx_check(rc, err, "if_message_on_mail") != SQLITE_OK)
        return jsn;
    else if (MX_VINT(jsn, "chat_type") == 1)
        get_notify_and_email(db, jsn);
    free(query);
    return jsn;
}
