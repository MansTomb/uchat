#include "client.h"

void mx_room_creation_build(t_info *info, t_room_creation *rc) {
    if (rc == NULL)
        info->windows->rc = rc = malloc(sizeof(t_room_creation));

    rc->builder = gtk_builder_new();
    gtk_builder_add_from_file(rc->builder, "./Resources/glade/room_creation.glade", NULL);

    rc->dialog = GTK_WIDGET(gtk_builder_get_object(rc->builder, "dialog"));
    rc->createbt = GTK_WIDGET(gtk_builder_get_object(rc->builder, "create"));
    rc->cancelbt = GTK_WIDGET(gtk_builder_get_object(rc->builder, "cancel"));
    rc->entry = GTK_WIDGET(gtk_builder_get_object(rc->builder, "name"));
    rc->roomcheck = GTK_WIDGET(gtk_builder_get_object(rc->builder, "room"));
    rc->channelcheck = GTK_WIDGET(gtk_builder_get_object(rc->builder, "channel"));
    gtk_builder_connect_signals(rc->builder, rc);

    rc->info = info;

    gtk_widget_show(rc->dialog);
}

void mx_room_creation_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->rc->dialog);
    free(info->windows->rc);
    info->windows->rc = NULL;
}

// void mx_on_click_create_room_channel(GtkWidget *widget, gpointer data) {
//     t_info *info = data;
//     t_room_creation *dialog = info->windows->room_creation;

//     gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dialog->groupbt), FALSE);
// }

// void mx_on_click_create_room_group(GtkWidget *widget, gpointer data) {
//     t_info *info = data;
//     t_room_creation *dialog = info->windows->room_creation;

//     gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dialog->channelbt), FALSE);
// }

// void mx_on_click_create_room_create(GtkWidget *widget, gpointer data) {
//     t_info *info = data;
//     t_room_creation *dialog = info->windows->room_creation;

    
//     if (mx_room_creation_data_validation(dialog)) {
//         // action "mx_make_new_chat" estimated return "mx_make_new_chat_success"(TODO)
//         mx_room_creation_destructor(info);
//     }
// }

// void mx_on_click_create_room_cancel(GtkWidget *widget, gpointer data) {
//     t_info *info = data;
//     t_room_creation *dialog = info->windows->room_creation;

//     mx_room_creation_destructor(info);
// }


