#include "client.h"

static void send_request(const t_info *info, int uid2) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", make_new_personal_chat);
    cJSON_AddNumberToObject(jobj, "uid1", info->cl_data->profile->id);
    cJSON_AddNumberToObject(jobj, "uid2", uid2);

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

static char *get_chat_name(t_info *info) {
    int uid2 = cJSON_GetObjectItem(info->json, "uid2")->valueint;

    if (info->cl_data->contacts) {
        t_list *list = info->cl_data->contacts;
        t_list_node *node = list ? list->head : NULL;

        for (int i = 0; node; node = node->next, ++i) {
            if (((t_contact *)node->data)->cid == uid2) {
                return mx_strdup(((t_contact *)node->data)->login);
            }
        }
    }
    return NULL;
}

static void push_chat(t_info *info) {
    int cid = cJSON_GetObjectItem(info->json, "cid")->valueint;
    int role = cJSON_GetObjectItem(info->json, "role")->valueint;
    char *cname = get_chat_name(info);
    
    if (MX_MALLOC_SIZE(cname) > 0) {
        mx_chat_put(info, cname, cid, 1);
        mx_strdel(&cname);
    }
    else {
        mx_dialog_warning_create(NULL, "Chat name error!");
    }
}

// TODO get true uid2
void mx_start_chat_json(t_info *info) {
    send_request(info, 2);
    mx_wait_for_json(info, success_new_personal_chat, failed_new_personal_chat);
    if (mx_get_jtype(info, success_new_personal_chat)) {
        push_chat(info);
        mx_dialog_warning_create(NULL, "Chat created!");
    }
    else {
        mx_dialog_warning_create(NULL, "Chat create error!");
    }
}
