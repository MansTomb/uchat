#include "client.h"

void mx_chat_put(t_info *info, char *chat_name) {
    t_chat *chat = mx_chat_build(info, chat_name);

    mx_push_back(info->chat_list, chat);
    gtk_stack_add_titled(GTK_STACK(info->windows->ms->chat_stack), chat->main_box, chat_name, chat_name);
}
