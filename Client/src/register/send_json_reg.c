#include "client.h"

static void reg_bld_json(const char *login, const char *password, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();
    char *string = NULL;

    cJSON_AddNumberToObject(jlogin, "json_type", make_register);
    cJSON_AddStringToObject(jlogin, "login", login);
    cJSON_AddStringToObject(jlogin, "hash", mx_create_hash((char *)password));

    string = cJSON_Print(jlogin);
    if (send(s_sock, string, strlen(string), 0) == -1)
        fprintf(stderr, "register: 'send' error occured\n");
    cJSON_Delete(jlogin);
    if (MX_MALLOC_SIZE(string))
        free(string);
}

void mx_register_build_json_wrapper(t_info *info) {
    reg_bld_json(mx_entry_get_text(info->windows->reg->username_entry),
                 mx_entry_get_text(info->windows->reg->password_entry),
                 info->sock->sock);
}
