#include "client.h"

static void send_request(const t_info *info, int coid) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", make_del_contact);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id);
    cJSON_AddNumberToObject(jobj, "coid", coid);

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

static void del_cnt(t_list *list, const cJSON *i) {
    if (list) {
        int cid = cJSON_GetObjectItemCaseSensitive(i, "coid")->valueint;
        t_list_node *node = list ? list->head : NULL;

        for (int i = 0; node; node = node->next, ++i) {
            if (((t_contact *)node->data)->cid == cid) {
                free(node->data);
                mx_pop_index(list, i);
                break;
            }
        }
    }
}

void mx_del_cnt_json(t_info *info) {
    int uid2 = mx_get_cnt_id_by_login(info->windows->cont->clicked_cont, info->cl_data->contacts);

    if (uid2 > 0) {
        send_request(info, 3);
        mx_wait_for_json(info, success_del_contact, failed_del_contact);
        if (mx_get_jtype(info, success_del_contact)) {
            if (MX_MALLOC_SIZE(info->cl_data->contacts) > 0) {
                del_cnt(info->cl_data->contacts, info->json);
            }
            mx_create_table(info, info->windows->cont);
        }
        else {
            mx_dialog_warning_create(NULL, "Failed del contact!");
        }
    }
    else {
        mx_dialog_warning_create(NULL, "Failed del contact!");
    }
}
