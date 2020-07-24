#include "client.h"

static void handlers2(t_info *info, cJSON *json, int type, int *ret) {
    if (type == success_leave_chat && !(*ret = 0))
        mx_handle_leave_room(info, json);
    else if (type == success_block_user && !(*ret = 0))
        mx_handle_ban(info, json);
    else if (type == success_unblock_user && !(*ret = 0))
        mx_handle_unban(info, json);
    else if (type == this_uid_login && !(*ret = 0))
        mx_handle_ulogin(info, json);
    else if (type == this_uid_logout && !(*ret = 0))
        mx_handle_ulogout(info, json);
}

bool mx_handle_if_not_requested(t_info *info, cJSON *json) {
    int type = cJSON_GetObjectItem(json, "json_type")->valueint;
    int ret = 1;

    if (type == send_message && !(ret = 0))
        mx_handle_send_message(info, json);
    else if (type == file_msg && !(ret = 0))
        mx_handle_send_message(info, json);
    else if (type == edit_message && !(ret = 0))
        mx_handle_edit_message(info, json);
    else if (type == delete_message && !(ret = 0))
        mx_handle_delete_message(info, json);
    else if (type == success_add_user_in_chat && !(ret = 0))
        mx_handle_invite_user(info, json);
    else if (type == add_user_in_chat_return_chat && !(ret = 0))
        mx_handle_being_invited(info, json);
    
    cJSON_Delete(json);
    return ret;
}
