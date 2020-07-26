#include "client.h"

void mx_on_click_create_room_channel(GtkWidget *widget, gpointer data) {
    t_room_creation *dialog = data;

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dialog->roomcheck),
                                                                       FALSE);
}

void mx_on_click_create_room_group(GtkWidget *widget, gpointer data) {
    t_room_creation *dialog = data;

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dialog->channelcheck),
                                                                       FALSE);
}

void mx_on_click_create_room_create(GtkWidget *widget, gpointer data) {
    t_room_creation *dialog = data;

    if (mx_room_creation_data_validation(dialog)) {
        mx_create_room_wrap(dialog->info);
        mx_room_creation_destroy(NULL, NULL, dialog->info);
    }
}

void mx_on_click_create_room_cancel(GtkWidget *widget, gpointer data) {
    t_room_creation *dialog = data;

    mx_room_creation_destroy(NULL, NULL, dialog->info);
}
