#include "client.h"

void mx_unban_user_build(t_info *info, t_chat *chat) {
    t_unban_user *unban = malloc(sizeof(t_unban_user));

    unban->builder = gtk_builder_new();
    gtk_builder_add_from_file(unban->builder, MX_GLADE_UNBAN, NULL);
    unban->dialog = mx_gobject_builder(unban->builder, "dialog");
    unban->entry = mx_gobject_builder(unban->builder, "entry");
    gtk_builder_connect_signals(unban->builder, unban);
    unban->info = info;
    unban->chat = chat;
    MX_GSIG_CON(unban->dialog, "delete-event", 
                                    G_CALLBACK(mx_unban_user_destroy), unban);
    gtk_widget_show(unban->dialog);
}

void mx_unban_user_destroy(GtkWidget *widget, GdkEvent *event, 
                                                        gpointer data) {
    t_unban_user *unban = data;

    gtk_widget_destroy(unban->dialog);
    free(unban);
}
