#include "client.h"

static void get_list_bld_json(const int id, int s_sock) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", make_search_user);
    cJSON_AddNumberToObject(jobj, "uid", id);

    mx_send_message_handler(jobj, s_sock);
    cJSON_Delete(jobj);
}

static t_user *get_user(const cJSON *iterator) {
    t_user *u = malloc(sizeof(t_user));

    u->id = cJSON_GetObjectItem(iterator, "uid")->valueint;
    u->login = cJSON_GetObjectItem(iterator, "login")->valuestring;
    return u;
}

static void save_users(t_info *info) {
    if (cJSON_IsObject(info->json)) {
        cJSON *iterator = NULL;
        cJSON *users = cJSON_GetObjectItem(info->json, "users");

        if (cJSON_IsArray(users)) {
            cJSON_ArrayForEach(iterator, users) {
                mx_push_back(info->cl_data->tmp_users, get_user(iterator));
            }
        }
        else
            fprintf(stderr, "json saving error\n");
    }
    else
        fprintf(stderr, "json saving error\n");
}

void mx_get_list_users_json_wrapper(t_info *info) {
    get_list_bld_json(info->cl_data->profile->id, info->sock->sock);
    mx_wait_for_json(info, failed_search_user, success_search_user);
    if (mx_get_jtype(info, success_search_user))
        save_users(info);
    else {
        mx_dialog_warning_create(NULL, "Failed search user!\n");
    }
}
