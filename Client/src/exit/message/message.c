#include "client.h"

void mx_chat_show_message(t_message *message) {
    gtk_widget_show(message->frame);
    gtk_widget_show(message->button);
    // gtk_widget_show(message->event);
    gtk_widget_show(message->icon);
    gtk_widget_show(message->lable);
    // gtk_widget_show(message->layout);
    // gtk_box_pack_start(GTK_BOX(chat->box), message->frame, TRUE, FALSE, 1);
}

void mx_chat_hide_message(t_message *message) {
    gtk_widget_hide(message->frame);
    gtk_widget_hide(message->button);
    // gtk_widget_hide(message->event);
    gtk_widget_hide(message->icon);
    gtk_widget_hide(message->lable);
    // gtk_widget_hide(message->layout);
    // gtk_box_pack_start(GTK_BOX(chat->box), message->frame, TRUE, FALSE, 1);
}
