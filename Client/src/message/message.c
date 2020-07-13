#include "client.h"

static void set_preferences(t_message *new, char *msg, int msgheight) {
    GtkWidget *lable;

    lable = gtk_bin_get_child(GTK_BIN(new->msg_bt));
    gtk_widget_set_size_request(new->msg_bt, MX_MSGWIDTH(msg), msgheight / 4);
    gtk_label_set_line_wrap(GTK_LABEL(lable), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(lable), PANGO_WRAP_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(lable), 50);
    gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);
    gtk_label_set_text(GTK_LABEL(lable), msg);

    gtk_widget_set_size_request(new->main_fixed, MX_MSGWIDTH(msg), msgheight / 4);
}

t_message *mx_message_build(t_info *info, char *username, char *msg) {
    t_message *message = malloc(sizeof(t_message));

    message->builder = gtk_builder_new();
    gtk_builder_add_from_file(message->builder, "./Resources/glade/message.glade", NULL);

    message->name_label = GTK_WIDGET(gtk_builder_get_object(message->builder, "username_label"));
    message->date_label = GTK_WIDGET(gtk_builder_get_object(message->builder, "date_label"));
    message->msg_bt = GTK_WIDGET(gtk_builder_get_object(message->builder, "msg_button"));
    message->menu = GTK_WIDGET(gtk_builder_get_object(message->builder, "menu"));
    message->main_fixed = GTK_WIDGET(gtk_builder_get_object(message->builder, "main_fixed"));
    set_preferences(message, msg, MX_MSGHEIGHT(msg));
    gtk_builder_connect_signals(message->builder, message);

    message->info = info;

    gtk_label_set_text(GTK_LABEL(message->name_label), username);
    gtk_widget_show(message->main_fixed);
    return message;
}

// void mx_message_destroy(t_info *info) {
//     gtk_widget_destroy(info->message->main_box);
//     free(info->message);
//     info->windows->log = NULL;
// }

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
