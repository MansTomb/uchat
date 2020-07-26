#include "client.h"

static int wrap(void *data) {
    t_chat *chat = data;

    mx_chat_destroy(chat->info, chat->cid);
    return 0;
}

void mx_handle_ban(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    int cid = cJSON_GetObjectItem(json, "cid")->valueint;
    int role = cJSON_GetObjectItem(json, "role")->valueint;
    t_chat *chat = mx_find_chat(info, cid);

    if (chat) {
        gdk_threads_add_idle(wrap, chat);
    }
}
