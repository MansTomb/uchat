#include "client.h"

static void free_wrapper(char **hash_pass, cJSON **jlogin) {
    cJSON_Delete(*jlogin);
    if (MX_MALLOC_SIZE(*hash_pass))
        free(*hash_pass);
}

static void request(t_info *info, const char *password, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();
    char *hash_pass = mx_create_hash(password);

    cJSON_AddNumberToObject(jlogin, "json_type", make_delete_user);
    cJSON_AddStringToObject(jlogin, "login", info->cl_data->profile->login);
    cJSON_AddStringToObject(jlogin, "hash", hash_pass);

    mx_send_message_handler(jlogin, s_sock);
    free_wrapper(&hash_pass, &jlogin);
}

void mx_delete_user_wrapper(t_info *info) {
    request(info, mx_entry_get_text(info->windows->dp->pass1), info->sock->sock);
    mx_wait_for_json(info, success_delete_user, failed_delete_user);
    if (mx_get_jtype(info, success_delete_user)) {
        mx_destroy(NULL, NULL, info);
    }
    else if (mx_get_jtype(info, failed_delete_user))
        mx_dialog_warning_create(NULL, "You'r suicide wasnt succesfull ;(");
}
