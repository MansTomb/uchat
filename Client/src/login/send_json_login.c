#include "client.h"

static void login_build_json(const char *login, const char *password, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();

    cJSON_AddNumberToObject(jlogin, "json_type", MX_MAKE_AUTORIZATION);
    cJSON_AddStringToObject(jlogin, "password", password);
    cJSON_AddStringToObject(jlogin, "login", login);

    char *string = cJSON_Print(jlogin);
    send(s_sock, string, sizeof(string), 0);
    cJSON_Delete(jlogin);
}


void mx_login_build_json_wrapper(t_info *info) {
    login_build_json(mx_entry_get_text(info->windows->log->password_entry),
                        mx_entry_get_text(info->windows->log->username_entry),
                        info->sock->sock);
}
