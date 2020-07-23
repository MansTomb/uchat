#include "client.h"

void mx_create_group_build(t_info *info, t_group_create *cg) {
    if (cg == NULL)
        info->windows->cg = cg = malloc(sizeof(t_group_create));

    cg->builder = gtk_builder_new();
    gtk_builder_add_from_file(cg->builder, "./Resources/glade/create_group.glade", NULL);

    cg->dialog = mx_gobject_builder(cg->builder, "dialog");
    cg->createbt = mx_gobject_builder(cg->builder, "create");
    cg->cancelbt = mx_gobject_builder(cg->builder, "cancel");
    cg->entry = mx_gobject_builder(cg->builder, "entry");
    gtk_builder_connect_signals(cg->builder, cg);

    cg->info = info;

    gtk_widget_show(cg->dialog);
}

void mx_create_group_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->cg->dialog);
    free(info->windows->cg);
    info->windows->cg = NULL;
}
