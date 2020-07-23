#include "client.h"

void mx_msg_img_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_message_img *message = data;

    gtk_popover_popup(GTK_POPOVER(message->menu));
}

void mx_msg_img_delete(GtkWidget *widget, gpointer data) {
    t_message_img *message = data;

    printf("Delete\n");
}

void mx_msg_open_folder(GtkWidget *widget, gpointer data) {
    t_message_img *message = data;
    char *command = mx_strjoin("open ", MX_RECV_FILES_DIR);

    system(command);
    mx_strdel(&command);
}
