#include "client.h"

static void send_get_chats_request(t_info *info) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", get_client_chats);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id); // we need to send our client uid

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

void save_chats(t_info *info) {
    for (int i = 0; i < cJSON_GetArraySize(cJSON_GetObjectItem(info->json, "chats")); ++i) {
        cJSON *chats = cJSON_GetArrayItem(cJSON_GetObjectItem(info->json, "chats"), i);
        char *cname = cJSON_GetObjectItem(chats, "cname")->valuestring;
        mx_chat_put(info, cname, cJSON_GetObjectItem(chats, "cid")->valueint);
        // mx_strdel(&cname);
        // cJSON_Delete(chats);
    }
}

void mx_get_json_chats_list(t_info *info) {
    send_get_chats_request(info);
    mx_wait_for_json(info, send_client_chats, send_client_chats);
    save_chats(info);
}
