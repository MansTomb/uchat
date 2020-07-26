#include "client.h"

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

void mx_change_contact_group(t_info *info) {
    int cid = mx_get_cnt_id_by_login(info->windows->cont->clicked_cont, info->cl_data->contacts);

    request(info, cid, 0, 1);
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
