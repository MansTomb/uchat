#include "client.h"

static void request(const t_info *info, t_chat *chat) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", get_client_chat_messages);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id); // we need to send our client uid
    cJSON_AddNumberToObject(jobj, "cid", chat->cid);

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

static void save(t_info *info, t_chat *chat) {
    if (cJSON_IsObject(info->json)) {
        cJSON *i = NULL;
        cJSON *messages = cJSON_GetObjectItem(info->json, "messages");
        t_message *msg = NULL;
        t_message_img *msg_img = NULL;

        if (cJSON_IsArray(messages)) {
            cJSON_ArrayForEach(i, messages) {
                if (cJSON_GetObjectItem(i, "mtype")->valueint == 1) {
                    msg = mx_message_build(info, i, chat->cid);
                    mx_message_put(info, msg, chat->cid);
                }
                else if (cJSON_GetObjectItem(i, "mtype")->valueint == 2) {
                    msg_img = mx_message_img_build(info, i, chat->cid);
                    mx_message_img_put(info, msg_img, chat->cid);
                }
            }
        }
    }
}

void mx_get_json_chat_history(t_info *info, t_chat *chat) {
    request(info, chat);
    mx_wait_for_json(info, send_client_chat_messages,
                                                 send_client_chat_messages);
    save(info, chat);
    info->json = NULL;
}
