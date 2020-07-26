#include "client.h"

void mx_change_password_build(t_info *info, t_change_password *cp) {
    if (cp == NULL)
        info->windows->cp = cp = malloc(sizeof(t_change_password));
    else
        return;

    cp->builder = gtk_builder_new();
    gtk_builder_add_from_file(cp->builder, "./Resources/glade/change_pass.glade", NULL);

    cp->dialog = mx_gobject_builder(cp->builder, "dialog");
    cp->changebt = mx_gobject_builder(cp->builder, "change");
    cp->cancelbt = mx_gobject_builder(cp->builder, "cancel");
    cp->oldpass = mx_gobject_builder(cp->builder, "oldpass");
    cp->newpass1 = mx_gobject_builder(cp->builder, "newpass1");
    cp->newpass2 = mx_gobject_builder(cp->builder, "newpass2");
    gtk_builder_connect_signals(cp->builder, cp);

    cp->info = info;

    gtk_widget_show(cp->dialog);
}

void mx_change_password_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->cp->dialog);
    free(info->windows->cp);
    info->windows->cp = NULL;
}
