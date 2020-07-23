#include "client.h"

void mx_unban_user_build(t_info *info) {
    t_unban_user *unban = malloc(sizeof(t_unban_user));

    unban->builder = gtk_builder_new();
    gtk_builder_add_from_file(unban->builder, "./Resources/glade/unban_user.glade", NULL);
    unban->dialog = mx_gobject_builder(unban->builder, "dialog");
    unban->entry = mx_gobject_builder(unban->builder, "entry");
    gtk_builder_connect_signals(unban->builder, unban);

    unban->info = info;

    gtk_widget_show(unban->dialog);
}

void mx_unban_user_destroy(t_unban_user *unban) {
    gtk_widget_destroy(unban->dialog);
    free(unban);
}
