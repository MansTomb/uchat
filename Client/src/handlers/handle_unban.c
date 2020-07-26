#include "client.h"

static int wrap(void *data) {
    t_ibear_info_json *dat = data;

    if (!mx_find_chat(dat->info, 
                            cJSON_GetObjectItem(dat->json, "cid")->valueint))
        mx_chat_put(dat->info, dat->json);
    free(dat);
    return 0;
}

void mx_handle_unban(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    t_ibear_info_json *data = malloc(sizeof(t_ibear_info_json));

    data->info = info;
    data->json = json;

    gdk_threads_add_idle(wrap, data);
}
