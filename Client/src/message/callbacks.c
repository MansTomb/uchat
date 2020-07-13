#include "client.h"

void mx_msg_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_message *message = data;

    gtk_popover_popup(GTK_POPOVER(message->menu));
}

void mx_msg_delete(GtkWidget *widget, gpointer data) {
    t_message *message = data;

    printf("Delete\n");
}

void mx_on_msg_edit(GtkWidget *widget, gpointer data) {
    t_message *message = data;

    printf("EditMsg\n");
}
