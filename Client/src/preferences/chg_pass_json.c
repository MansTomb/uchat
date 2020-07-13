#include "client.h"

static void del_wrapper(char **hash_old, char **hash_new, cJSON **jobj) {
    mx_strdel(hash_old);
    mx_strdel(hash_new);
    if (MX_MALLOC_SIZE(*jobj))
        cJSON_Delete(*jobj);
}

static void send_request(const t_info *info, const char *old_pass, const char *new_pass) {
    cJSON *jobj = cJSON_CreateObject();
    char *hash_old = mx_create_hash(old_pass);
    char *hash_new = mx_create_hash(new_pass);

    cJSON_AddNumberToObject(jobj, "json_type", make_change_password);
    cJSON_AddStringToObject(jobj, "login", info->cl_data->profile->login);
    cJSON_AddStringToObject(jobj, "hash", hash_old);
    cJSON_AddStringToObject(jobj, "new_hash", hash_new);

    mx_send_message_handler(jobj, info->sock->sock);
    del_wrapper(&hash_old, &hash_new, &jobj);
}

void mx_chg_pass_json(t_info *info, const char *old_pass, const char *new_pass) {
    send_request(info, old_pass, new_pass);
    mx_wait_for_json(info, success_change_password, failed_change_password);
    if (mx_get_jtype(info, failed_change_password)) {
        mx_dialog_warning_create(NULL, "Failed change password!\n");
    }
}
