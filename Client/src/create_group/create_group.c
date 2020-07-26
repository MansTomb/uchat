#include "client.h"

void mx_create_group_build(t_info *info, t_group_create *cg) {
    if (cg == NULL)
        info->windows->cg = cg = malloc(sizeof(t_group_create));
    else
        return;

    cg->builder = gtk_builder_new();
    gtk_builder_add_from_file(cg->builder, MX_GLADE_CG, NULL);

    cg->dialog = mx_gobject_builder(cg->builder, "dialog");
    cg->createbt = mx_gobject_builder(cg->builder, "create");
    cg->cancelbt = mx_gobject_builder(cg->builder, "cancel");
    cg->entry = mx_gobject_builder(cg->builder, "entry");
    gtk_builder_connect_signals(cg->builder, cg);
    cg->info = info;
    MX_GSIG_CON(cg->dialog, "delete-event", 
                                G_CALLBACK(mx_create_group_destroy), cg->info);
    gtk_widget_show(cg->dialog);
}

void mx_create_group_destroy(GtkWidget *widget, GdkEvent *event, 
                                                            gpointer data) {
    t_info *info = data;

    gtk_widget_destroy(info->windows->cg->dialog);
    free(info->windows->cg);
    info->windows->cg = NULL;
}
