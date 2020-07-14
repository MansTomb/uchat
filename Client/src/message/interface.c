#include "client.h"

void mx_message_put(t_info *info, t_message *msg, int cid) {
    t_chat *chat = mx_find_chat(info, cid); // get chat by id from list

    mx_push_front(chat->msg_list, msg);
    gtk_list_box_insert(GTK_LIST_BOX(chat->message_box), msg->main_fixed, -1);
}
