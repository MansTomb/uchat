#include "client.h"

void mx_on_click_create_room_channel(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_room_creation *dialog = info->windows->room_creation;

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dialog->groupbt), FALSE);
    if(widget){};
}

void mx_on_click_create_room_group(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_room_creation *dialog = info->windows->room_creation;

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dialog->channelbt), FALSE);
    if(widget){};
}

void mx_on_click_create_room_create(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_room_creation *dialog = info->windows->room_creation;

    // create room json and send

    mx_room_creation_destructor(info);
    if(widget && dialog) {};
}

void mx_on_click_create_room_cancel(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_room_creation *dialog = info->windows->room_creation;

    mx_room_creation_destructor(info);
    if(widget && dialog) {};
}
