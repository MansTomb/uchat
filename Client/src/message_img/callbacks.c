#include "client.h"

void mx_msg_img_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_message_img *message = data;

    gtk_popover_popup(GTK_POPOVER(message->menu));
}

void mx_msg_img_delete(GtkWidget *widget, gpointer data) {
    t_message_img *message = data;

    printf("Delete\n");
}
