#include "client.h"

static void send_get_request(const t_info *info, const char *gname) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", make_add_contact_group);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id);
    cJSON_AddStringToObject(jobj, "gname", gname);

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

void mx_send_json_group(t_info *info, const char *gname) {
    send_get_request(info, gname);
    mx_wait_for_json(info, success_add_contact_group, failed_add_contact_group);
    if (mx_get_jtype(info, success_add_contact_group)) {
        mx_get_json_contacts(info);
    }
}
