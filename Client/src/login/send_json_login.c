#include "client.h"

static void log_bld_json(const char *login, const char *password, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();
    char *string = NULL;

    cJSON_AddNumberToObject(jlogin, "json_type", make_authorization);
    cJSON_AddStringToObject(jlogin, "login", login);
    cJSON_AddStringToObject(jlogin, "hash", mx_create_hash((char *)password));

    string = cJSON_Print(jlogin);
    if (!string || send(s_sock, string, strlen(string), 0) == -1)
        fprintf(stderr, "login: 'send' error occured\n");
    cJSON_Delete(jlogin);
    if (MX_MALLOC_SIZE(string))
        free(string);
}

void mx_login_build_json_wrapper(t_info *info) {
    log_bld_json(mx_entry_get_text(info->windows->log->username_entry),
                 mx_entry_get_text(info->windows->log->password_entry),
                 info->sock->sock);
}
