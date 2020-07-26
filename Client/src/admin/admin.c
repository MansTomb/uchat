#include "client.h"

void mx_admin_screen_build(t_info *info, t_admin *adm) {
    if (adm == NULL)
        info->windows->adm = adm = malloc(sizeof(t_admin));

    adm->builder = gtk_builder_new();
    gtk_builder_add_from_file(adm->builder, MX_GLADE_ADMIN, NULL);

    adm->message_tv = mx_gobject_builder(adm->builder, "text_view");
    adm->backbt = mx_gobject_builder(adm->builder, "back");
    adm->sendbt = mx_gobject_builder(adm->builder, "send");
    adm->window = mx_gobject_builder(adm->builder, "window");
    gtk_builder_connect_signals(adm->builder, info);

    mx_css_from_file(info, "./Resources/css/admin.css");
    gtk_widget_show(adm->window);
}

void mx_admin_screen_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->adm->window);
    free(info->windows->adm);
    info->windows->adm = NULL;
}
