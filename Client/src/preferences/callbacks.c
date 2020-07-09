#include "client.h"

void mx_on_toggle_vnoti(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_preferences *pref = info->windows->pref;

    info->cl_data->profile->vs_noty = mx_get_tactive(pref->vnotify);
}

void mx_on_toggle_snoti(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_preferences *pref = info->windows->pref;

    info->cl_data->profile->sound_noty = mx_get_tactive(pref->snotify);
}

void mx_on_toggle_enoti(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_preferences *pref = info->windows->pref;

    info->cl_data->profile->email_noty = mx_get_tactive(pref->enotify);
}

void mx_on_change_password(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_preferences *pref = info->windows->pref;

    mx_change_password_build(info, info->windows->cp);
    // change password dialog
}
