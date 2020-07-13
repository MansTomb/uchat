#include "client.h"

static t_chat *find_chat(t_info *info, int cid) {
    t_list *clist = info->chat_list;
    t_chat *chat = NULL;

    for (size_t i = 0; i < clist->size; ++i) {
        chat = mx_get_index(clist, i)->data;
        if (chat->cid == cid)
            return chat;
    }
    return NULL;
}

void mx_message_put(t_info *info, t_message *msg, int cid) {
    t_chat *chat = find_chat(info, cid); // get chat by id from list

    mx_push_front(chat->msg_list, msg);
    gtk_list_box_insert(GTK_LIST_BOX(chat->message_box), msg->main_fixed, -1);
}
