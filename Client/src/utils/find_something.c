#include "client.h"

t_chat *mx_find_chat(t_info *info, int cid) {
    t_list *clist = info->chat_list;
    t_chat *chat = NULL;

    for (size_t i = 0; i < clist->size; ++i) {
        chat = mx_get_index(clist, i)->data;
        if (chat->cid == cid)
            return chat;
    }
    return NULL;
}

t_message *mx_find_message(t_chat *chat, int mid) {
    t_list *msglist = chat->msg_list;
    t_message *msg = NULL;

    for (size_t i = 0; i < msglist->size; ++i) {
        msg = mx_get_index(msglist, i)->data;
        if (msg->mid == mid)
            return msg;
    }
    return NULL;
}
