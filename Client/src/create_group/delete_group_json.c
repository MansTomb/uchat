#include "client.h"

static void send_request(const t_info *info, int gid) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", make_del_contact_group);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id);
    cJSON_AddNumberToObject(jobj, "gid", gid);

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

static void del_grp(t_list *list, const cJSON *i) {
    if (list) {

        int gid = cJSON_GetObjectItemCaseSensitive(i, "gid")->valueint;
        t_list_node *node = list ? list->head : NULL;

        for (int i = 0; node; node = node->next, ++i) {
            if (((t_group *)node->data)->id == gid) {
                free(node->data);
                mx_pop_index(list, i);
                break;
            }
        }
    }
}

static int get_gid(const t_list *list, const char* gname) {
    if (list) {
        t_list_node *node = list ? list->head : NULL;

        for (int i = 0; node; node = node->next, ++i) {
            if (strcmp(((t_group *)node->data)->name, gname) == 0) {
                return (((t_group *)node->data)->id);
            }
        }
    }
    return -1;
}

void mx_del_group_json(t_info *info) {
    const char *gname = info->windows->cont->clicked_cont;
    int gid = get_gid(info->cl_data->cont_grp_names, gname);

    if (gid > 0) {
        send_request(info, gid);
        mx_wait_for_json(info, success_del_contact_group, failed_del_contact_group);
        if (mx_get_jtype(info, success_del_contact_group)
            && MX_MALLOC_SIZE(info->cl_data->cont_grp_names) > 0) {
            del_grp(info->cl_data->cont_grp_names, info->json);
            mx_create_table(info, info->windows->cont);
        }
        else {
            mx_dialog_warning_create(NULL, "Failed del group!");
        }
    }
    else {
        mx_dialog_warning_create(NULL, "Failed del group!");
    }
}
