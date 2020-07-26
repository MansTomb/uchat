#include "client.h"

static void send_request(const t_info *info, int uid2) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", make_new_personal_chat);
    cJSON_AddNumberToObject(jobj, "uid1", info->cl_data->profile->id);
    cJSON_AddNumberToObject(jobj, "uid2", uid2);

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

int mx_get_cnt_id_by_login(const char *login, const t_list *list) {
    if (list) {
        t_list_node *node = list ? list->head : NULL;

        for (int i = 0; node; node = node->next, ++i) {
            if (strcmp(((t_contact *)node->data)->login, login) == 0) {
                return (((t_contact *)node->data)->cid);
            }
        }
    }
    return -1;
}

void mx_start_chat_json(t_info *info) {
    int uid2 = mx_get_cnt_id_by_login(info->windows->cont->clicked_cont,
                                                     info->cl_data->contacts);

    if (uid2 >= 0) {
        send_request(info, uid2);
    }
}
