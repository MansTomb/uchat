#include "client.h"

static int wrap(void *data) {
    mx_set_chat_preferences(data);
    return 0;
}

void mx_handle_ban(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    int cid = cJSON_GetObjectItem(json, "cid")->valueint;
    int role = cJSON_GetObjectItem(json, "role")->valueint;
    t_chat *chat = mx_find_chat(info, cid);

    if (chat) {
        chat->role = role;
        gdk_threads_add_idle(wrap, chat);
    }
}
