#include "client.h"

static void request(t_info *info, int ctype, char *cname) {
    cJSON *request = cJSON_CreateObject();

    cJSON_AddNumberToObject(request, "json_type", make_new_group_chat_channel);
    cJSON_AddNumberToObject(request, "uid", info->cl_data->profile->id);
    cJSON_AddNumberToObject(request, "ctype", ctype);
    cJSON_AddStringToObject(request, "cname", cname);

    mx_send_message_handler(request, info->sock->sock);
    cJSON_Delete(request);
}

static void push_chat(t_info *info) {
    int jtype = cJSON_GetObjectItem(info->json, "json_type")->valueint;
    int cid = cJSON_GetObjectItem(info->json, "cid")->valueint;
    int ctype = cJSON_GetObjectItem(info->json, "ctype")->valueint;
    char *cname = cJSON_GetObjectItem(info->json, "cname")->valuestring;
    
    if (jtype != failed_new_group_chat_channel) {};
        // mx_chat_put();
}

void mx_create_room_wrap(t_info *info) {
    t_room_creation *rc = info->windows->rc;
    int ctype = gtk_toggle_button_get_active(
                                    GTK_TOGGLE_BUTTON(rc->roomcheck)) ? 1 : 2;

    request(info, ctype, (char *)mx_entry_get_text(rc->entry));
    mx_wait_for_json(info, success_new_group_chat_channel, failed_new_group_chat_channel);
    push_chat(info);
}
