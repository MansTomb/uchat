#include "client.h"

static int wrap(void *data) {
    t_ibear_info_json *info = data;

    mx_chat_put(info->info, info->json);
    free(data);
    return 0;
}

void mx_handle_ucreate_chat(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    t_ibear_info_json *info_v2 = malloc(sizeof(t_ibear_info_json));
    int cid = cJSON_GetObjectItem(json, "cid")->valueint;
    t_chat *chat = mx_find_chat(info, cid);

    info_v2->info = info;
    info_v2->json = json;

    if (!chat)
        gdk_threads_add_idle(wrap, info_v2);
}
