#include "client.h"

static void free_wrapper(char **hash_pass, cJSON **jreg) {
    cJSON_Delete(*jreg);
    if (MX_MALLOC_SIZE(*hash_pass))
        free(*hash_pass);
}

static void reg_bld_json(const char *login, const char *password, int s_sock) {
    cJSON *jreg = cJSON_CreateObject();
    char *hash_pass = mx_create_hash(password);

    cJSON_AddNumberToObject(jreg, "json_type", make_register);
    cJSON_AddStringToObject(jreg, "login", login);
    cJSON_AddStringToObject(jreg, "hash", hash_pass);
    mx_send_message_handler(jreg, s_sock);
    free_wrapper(&hash_pass, &jreg);
}

void mx_register_build_json_wrapper(t_info *info) {
    reg_bld_json(mx_entry_get_text(info->windows->reg->username_entry),
                 mx_entry_get_text(info->windows->reg->password_entry),
                 info->sock->sock);
}
