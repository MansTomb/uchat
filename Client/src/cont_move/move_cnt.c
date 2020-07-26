#include "client.h"

static int get_group_id(t_info *info, char *name) {
    t_group *node = NULL;

    for (size_t i = 0; i < info->cl_data->cont_grp_names->size; ++i) {
        node = mx_get_index(info->cl_data->cont_grp_names, i)->data;
        if (strcmp(node->name, name) == 0)
            return node->id;
    }
    return -1;
}

static void request(t_info *info, int cid, int gid1, int gid2) {
    cJSON *request = cJSON_CreateObject();

    cJSON_AddNumberToObject(request, "json_type", make_change_contact_group);
    cJSON_AddNumberToObject(request, "uid", info->cl_data->profile->id);
    cJSON_AddNumberToObject(request, "cid", cid);
    cJSON_AddNumberToObject(request, "gid1", gid1);
    cJSON_AddNumberToObject(request, "gid2", gid2);

    mx_send_message_handler(request, info->sock->sock);
    cJSON_Delete(request);
}

void mx_change_contact_group(t_info *info, char *name) {
    int cid = mx_get_cnt_id_by_login(info->windows->cont->clicked_cont, info->cl_data->contacts);
    t_contact *cont = mx_find_contant(info, cid);

    request(info, cid, cont->grp_id, get_group_id(info, name));
    mx_wait_for_json(info, success_change_contact_group, failed_change_contact_group);
    if (mx_get_jtype(info, success_change_contact_group)) {
        mx_get_json_contacts(info);
        mx_create_table(info, info->windows->cont);
        mx_dialog_warning_create(NULL, "Successfully changed!");
    }
    else {
        mx_dialog_warning_create(NULL, "Error changing group!");
    }
}
