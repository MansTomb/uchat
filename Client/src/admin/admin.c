#include "client.h"

void mx_admin_screen_show(t_info *info) {
    t_admin *admin = info->windows->admin;

    if (!admin)
        admin = info->windows->admin = mx_admin_constructor(info);

    gtk_widget_show(admin->entry_field);
    gtk_widget_show(admin->send_button);
    gtk_widget_show(admin->unlog_button);
}

void mx_admin_screen_hide(t_info *info) {
    t_admin *admin = info->windows->admin;

    gtk_widget_hide(admin->entry_field);
    gtk_widget_hide(admin->send_button);
    gtk_widget_hide(admin->unlog_button);
}
