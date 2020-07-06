#include "client.h"

static void set_preferences(t_message_img *new, char *username, GtkWidget *img) {
    gtk_widget_set_size_request(new->main_fixed, 200, 200);
    gtk_button_set_image(GTK_BUTTON(new->msg_bt), img);
    gtk_label_set_text(GTK_LABEL(new->name_label), username);
}

t_message_img *mx_message_img_build(t_info *info, char *username, GtkWidget *img) {
    t_message_img *message = malloc(sizeof(t_message_img));

    message->builder = gtk_builder_new();
    gtk_builder_add_from_file(message->builder, "./Resources/glade/message_img.glade", NULL);

    message->name_label = GTK_WIDGET(gtk_builder_get_object(message->builder, "username_label"));
    message->date_label = GTK_WIDGET(gtk_builder_get_object(message->builder, "date_label"));
    message->msg_bt = GTK_WIDGET(gtk_builder_get_object(message->builder, "msg_button"));
    message->menu = GTK_WIDGET(gtk_builder_get_object(message->builder, "menu"));
    message->main_fixed = GTK_WIDGET(gtk_builder_get_object(message->builder, "main_fixed"));
    gtk_builder_connect_signals(message->builder, message);
    set_preferences(message, username, img);

    message->info = info;

    gtk_widget_show(message->main_fixed);
    return message;
}

// void mx_message_destroy(t_info *info) {
//     gtk_widget_destroy(info->message->main_box);
//     free(info->message);
//     info->windows->log = NULL;
// }

void mx_msg_img_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_message_img *message = data;

    gtk_popover_popup(GTK_POPOVER(message->menu));
}

void mx_msg_img_delete(GtkWidget *widget, gpointer data) {
    t_message_img *message = data;

    printf("Delete\n");
}
