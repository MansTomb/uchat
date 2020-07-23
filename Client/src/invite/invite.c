#include "client.h"

void mx_invite_user_build(t_info *info) {
    t_invite_user *inv = malloc(sizeof(t_invite_user));

    inv->builder = gtk_builder_new();
    gtk_builder_add_from_file(inv->builder, "./Resources/glade/invite_user.glade", NULL);
    inv->dialog = mx_gobject_builder(inv->builder, "dialog");
    inv->entry = mx_gobject_builder(inv->builder, "entry");
    gtk_builder_connect_signals(inv->builder, inv);

    inv->info = info;

    gtk_widget_show(inv->dialog);
}

void mx_invite_user_destroy(t_invite_user *inv) {
    gtk_widget_destroy(inv->dialog);
    free(inv);
}
