#include "client.h"

static void free_wrapper(char **hash_pass, cJSON **jlogin) {
    cJSON_Delete(*jlogin);
    if (MX_MALLOC_SIZE(*hash_pass))
        free(*hash_pass);
}

static void log_bld_json(const char *login, const char *password, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();
    char *hash_pass = mx_create_hash(password);

    cJSON_AddNumberToObject(jlogin, "json_type", make_authorization);
    cJSON_AddStringToObject(jlogin, "login", login);
    cJSON_AddStringToObject(jlogin, "hash", hash_pass);

    mx_send_message_handler(jlogin, s_sock);
    free_wrapper(&hash_pass, &jlogin);
}

void mx_login_build_json_wrapper(t_info *info) {
    log_bld_json(mx_entry_get_text(info->windows->log->username_entry),
                 mx_entry_get_text(info->windows->log->password_entry),
                 info->sock->sock);
}

void mx_save_login_data(t_info *info) {
    t_profile_data *p = info->cl_data->profile;

    p->id = cJSON_GetObjectItem(info->json, "uid")->valueint;
    p->login = cJSON_GetObjectItem(info->json, "login")->valuestring;
    p->first_name = cJSON_GetObjectItem(info->json, "fname")->valuestring;
    p->sec_name = cJSON_GetObjectItem(info->json, "sname")->valuestring;
    p->user_email = cJSON_GetObjectItem(info->json, "email")->valuestring;
    p->status = cJSON_GetObjectItem(info->json, "status")->valuestring;

    p->sound_noty = cJSON_GetObjectItem(info->json, "snotify")->valueint;
    p->vs_noty = cJSON_GetObjectItem(info->json, "vnotify")->valueint;
    p->email_noty = cJSON_GetObjectItem(info->json, "enotify")->valueint;
}
