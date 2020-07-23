#include "client.h"

bool mx_handle_if_not_requested(t_info *info, cJSON *json) {
    int type = cJSON_GetObjectItem(json, "json_type")->valueint;
    int ret = 1;

    if (type == send_message && (ret = 0))
        mx_handle_send_message(info, json);
    else if (type == file_msg && (ret = 0))
        mx_handle_send_message(info, json);
    else if (type == edit_message && (ret = 0))
        mx_handle_edit_message(info, json);
    else if (type == delete_message && (ret = 0))
        mx_handle_delete_message(info, json);
    else if (type == invited_user)
        mx_handle_invite_user(info, json);
    cJSON_Delete(json);
    return ret;
}
