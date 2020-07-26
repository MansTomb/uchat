#include "client.h"

void mx_invite_user_build(t_info *info, t_chat *chat) {
    t_invite_user *inv = malloc(sizeof(t_invite_user));

    inv->builder = gtk_builder_new();
    gtk_builder_add_from_file(inv->builder,
                              "./Resources/glade/invite_user.glade", NULL);
    inv->dialog = mx_gobject_builder(inv->builder, "dialog");
    inv->entry = mx_gobject_builder(inv->builder, "entry");
    gtk_builder_connect_signals(inv->builder, inv);

    inv->info = info;
    inv->chat = chat;
    MX_GSIG_CON(inv->dialog, "delete-event", 
                                    G_CALLBACK(mx_invite_user_destroy), inv);

    gtk_widget_show(inv->dialog);
}

void mx_invite_user_destroy(GtkWidget *widget, GdkEvent *event, 
                                                            gpointer data) {
    t_invite_user *inv = data;

    gtk_widget_destroy(inv->dialog);
    free(inv);
}
