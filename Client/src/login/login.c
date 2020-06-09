#include "client.h"

void mx_login_screen_show(t_info *info) {
    t_login *log = info->windows->log;

    if (!log)
        log = info->windows->log = mx_login_constructor(info);

    mx_background_image_show(log->back_image);
    gtk_widget_show(log->username_label);
    gtk_widget_show(log->username_entry);
    gtk_widget_show(log->password_entry);
    gtk_widget_show(log->password_label);
    gtk_widget_show(log->loginbt);
    gtk_widget_show(log->registerbt);
}

void mx_login_screen_hide(t_info *info) {
    t_login *log = info->windows->log;

    gtk_widget_hide(log->loginbt);
    gtk_widget_hide(log->registerbt);
    gtk_widget_hide(log->username_label);
    gtk_widget_hide(log->username_entry);
    gtk_widget_hide(log->password_entry);
    gtk_widget_hide(log->password_label);
    mx_background_image_hide(log->back_image);
}
