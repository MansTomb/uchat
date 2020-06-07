#include "client.h"

void mx_chat_switcher_add_chat(t_info *info, t_chat *chat, char *chat_name, char *chat_title ) {
    mx_stack_add(info->windows->chat_switcher->stack, chat->scroll, chat_name, chat_title);
}
