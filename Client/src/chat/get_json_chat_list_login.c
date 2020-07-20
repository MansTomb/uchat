#include "client.h"

static void send_get_chats_request(const t_info *info) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", get_client_chats);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id); // we need to send our client uid

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

static void save_chats(t_info *info) {
    if (cJSON_IsObject(info->json)) {
        cJSON *i = NULL;
        cJSON *chats = cJSON_GetObjectItem(info->json, "chats");

        if (cJSON_IsArray(chats)) {
            cJSON_ArrayForEach(i, chats) {
                mx_chat_put(info,
                            cJSON_GetObjectItem(i, "cname")->valuestring,
                            cJSON_GetObjectItem(i, "cid")->valueint,
                            cJSON_GetObjectItem(i, "ctype")->valueint
                            );
            }
        }
        else
            fprintf(stderr, "json saving error\n");
    }
    else
        fprintf(stderr, "json saving error\n");
}

void mx_get_json_chats_list(t_info *info) {
    send_get_chats_request(info);
    mx_wait_for_json(info, send_client_chats, send_client_chats);
    if (mx_get_jtype(info, send_client_chats)) {
        save_chats(info);
    }
}
