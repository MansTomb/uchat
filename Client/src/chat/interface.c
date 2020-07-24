#include "client.h"

void mx_chat_put(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    t_chat *chat = mx_chat_build(info, json);
    char name[64];

    sprintf(name, "%d", chat->cid);

    mx_push_back(info->chat_list, chat);
    gtk_stack_add_titled(GTK_STACK(info->windows->ms->chat_stack), chat->main_box, name, chat->chat_name);
    mx_get_json_chat_history(info, chat);
}
