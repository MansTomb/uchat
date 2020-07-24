#include "client.h"

void mx_handle_unban(t_info *info, cJSON *json) {
    int cid = cJSON_GetObjectItem(json, "cid")->valueint;
    int role = cJSON_GetObjectItem(json, "role")->valueint;
    t_chat *chat = mx_find_chat(info, cid);

    chat->role = role;
    mx_set_chat_preferences(chat);
}
