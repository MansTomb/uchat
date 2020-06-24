#include "client.h"

static void free_wrapper(char **str, char **hash_pass, cJSON **jlogin) {
    cJSON_Delete(*jlogin);
    if (MX_MALLOC_SIZE(str))
        free(*str);
    if (MX_MALLOC_SIZE(hash_pass))
        free(*hash_pass);
}

static void reg_bld_json(const char *login, const char *password, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();
    char *str = NULL;
    char *hash_pass = mx_create_hash(password);

    cJSON_AddNumberToObject(jlogin, "json_type", make_register);
    cJSON_AddStringToObject(jlogin, "login", login);
    cJSON_AddStringToObject(jlogin, "hash", hash_pass);

    str = cJSON_Print(jlogin);
    if (!str || send(s_sock, str, strlen(str), 0) == -1)
        fprintf(stderr, "register: 'send' error occured\n");
    free_wrapper(&str, &hash_pass, &jlogin);
}

void mx_register_build_json_wrapper(t_info *info) {
    reg_bld_json(mx_entry_get_text(info->windows->reg->username_entry),
                 mx_entry_get_text(info->windows->reg->password_entry),
                 info->sock->sock);
}
