#include "client.h"

void mx_on_click_create_room_channel(GtkWidget *widget, gpointer data) {
    t_room_creation *dialog = data;

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dialog->roomcheck), FALSE);
}

void mx_on_click_create_room_group(GtkWidget *widget, gpointer data) {
    t_room_creation *dialog = data;

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dialog->channelcheck), FALSE);
}

void mx_on_click_create_room_create(GtkWidget *widget, gpointer data) {
    t_room_creation *dialog = data;

    
    if (mx_room_creation_data_validation(dialog)) {
        // action "mx_make_new_chat" estimated return "mx_make_new_chat_success"(TODO)
        // check if need to create group(if false then create channel) -> gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(dialog->roomcheck));
        // Get room name -> mx_entry_get_text(dialog->entry)
        mx_room_creation_destroy(dialog->info);
    }
}

void mx_on_click_create_room_cancel(GtkWidget *widget, gpointer data) {
    t_room_creation *dialog = data;

    mx_room_creation_destroy(dialog->info);
}
