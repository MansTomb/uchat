#include "client.h"

void mx_chat_put(t_info *info, char *chat_name, int cid) {
    t_chat *chat = mx_chat_build(info, chat_name, cid);
    char name[64];

    sprintf(name, "%d", cid);

    mx_push_back(info->chat_list, chat);
    gtk_stack_add_titled(GTK_STACK(info->windows->ms->chat_stack), chat->main_box, name, chat_name);
    mx_get_json_chat_history(info, chat);
}
