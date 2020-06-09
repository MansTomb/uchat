#include "client.h"

static void show_all_messages(t_list_node *node) {
    mx_chat_show_message(node->data);
    // printf("%p\n", (void *)node->data);
}

static void hide_all_messages(t_list_node *node) {
    mx_chat_hide_message(node->data);
    // printf("%p\n", (void *)node->data);
}

void mx_chat_screen_show(t_chat *chat) {
    gtk_widget_show(chat->scroll);
    gtk_widget_show(chat->layout);
    gtk_widget_show(chat->box);
    gtk_widget_show(chat->sendbt);
    gtk_widget_show(chat->msgentry);
    chat->showed_chat = 1;
    mx_foreach_list(chat->messages, show_all_messages);
}
void mx_chat_screen_hide(t_chat *chat) {
    gtk_widget_hide(chat->scroll);
    gtk_widget_hide(chat->layout);
    gtk_widget_hide(chat->box);
    gtk_widget_hide(chat->sendbt);
    gtk_widget_hide(chat->msgentry);
    chat->showed_chat = 0;
    mx_foreach_list(chat->messages, hide_all_messages);
}

void mx_chat_message_put(t_chat *chat, t_message *message) {
    mx_push_back(chat->messages, message);
    gtk_list_box_insert(GTK_LIST_BOX(chat->box), message->frame, -1);
    mx_chat_screen_show(chat);
}
