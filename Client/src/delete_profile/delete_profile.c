#include "client.h"

void mx_delete_profile_build(t_info *info, t_delete_profile *dp) {
    if (dp == NULL)
        info->windows->dp = dp = malloc(sizeof(t_group_create));
    else
        return;

    dp->builder = gtk_builder_new();
    gtk_builder_add_from_file(dp->builder, MX_GLADE_DP, NULL);
    dp->dialog = mx_gobject_builder(dp->builder, "dialog");
    dp->pass1 = mx_gobject_builder(dp->builder, "pass1");
    dp->pass2 = mx_gobject_builder(dp->builder, "pass2");
    gtk_builder_connect_signals(dp->builder, dp);
    dp->info = info;
    MX_GSIG_CON(dp->dialog, "delete-event", 
                              G_CALLBACK(mx_delete_profile_destroy), dp->info);
    gtk_widget_show(dp->dialog);
}

void mx_delete_profile_destroy(GtkWidget *widget, GdkEvent *event, 
                                                            gpointer data) {
    t_info *info = data;

    gtk_widget_destroy(info->windows->dp->dialog);
    free(info->windows->dp);
    info->windows->dp = NULL;
}
