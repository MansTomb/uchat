#include "client.h"

void mx_login_build_json(const char *login, const char *password, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();

    cJSON_AddNumberToObject(jlogin, "json_type", 1);
    cJSON_AddStringToObject(jlogin, "password", password);
    cJSON_AddStringToObject(jlogin, "login", login);

    char *string = cJSON_Print(jlogin);
    send(s_sock, string, sizeof(string), 0);
    // printf("%s\n", string);
    cJSON_Delete(jlogin);
}


void mx_login_entry_empty(t_info *info) {
    mx_dialog_warning_create(info->main_window, "Fields cant be empty!");
}
