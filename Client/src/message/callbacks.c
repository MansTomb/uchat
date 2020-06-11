#include "client.h"

void mx_callback_reply(GtkWidget *widget, gpointer data) {
    if (widget && data) {};
    printf("reply\n");
}

void mx_callback_forward(GtkWidget *widget, gpointer data) {
    if (widget && data) {};
    printf("forward\n");
}

void mx_callback_delete(GtkWidget *widget, gpointer data) {
    if (widget && data) {};
    printf("delete\n");
}

void mx_callback_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_message *message = data;

    gtk_menu_popup_at_pointer(GTK_MENU(message->menu), event);
    if(widget && message) {};
}
