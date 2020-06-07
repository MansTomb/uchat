#include "client.h"

void mx_chat_screen_show(t_chat *chat) {
    gtk_widget_show(chat->scroll);
    gtk_widget_show(chat->layout);
    gtk_widget_show(chat->box);
}
void mx_chat_screen_hide(t_chat *chat) {
    gtk_widget_hide(chat->scroll);
    gtk_widget_hide(chat->layout);
    gtk_widget_hide(chat->box);
}

void mx_chat_show_message(t_chat *chat, char *sender, char *text) {
    t_message *message = mx_message_construct(text, sender);

    gtk_box_pack_start(GTK_BOX(chat->box), message->frame, TRUE, FALSE, 5);
}
