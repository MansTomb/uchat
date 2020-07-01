#include "client.h"

void mx_preferences_show(t_info *info) {
    t_preferences *pref = info->windows->preferences;

    if (pref == NULL)
        pref = info->windows->preferences = mx_preferences_constructor(info);

    info->current_window = info->windows->preferences;

    gtk_widget_show(pref->scroll);
    gtk_widget_show(pref->layout);
    gtk_widget_show(pref->volume_label);
    gtk_widget_show(pref->volume);
    gtk_widget_show(pref->theme_label);
    gtk_widget_show(pref->theme_switch);
    gtk_widget_show(pref->s_notify_switch);
    gtk_widget_show(pref->v_notify_switch);
    gtk_widget_show(pref->e_notify_switch);
}

void mx_preferences_hide(t_info *info) {
    t_preferences *pref = info->windows->preferences;

    info->current_window = NULL;

    gtk_widget_hide(pref->scroll);
    gtk_widget_hide(pref->layout);
    gtk_widget_hide(pref->volume_label);
    gtk_widget_hide(pref->volume);
    gtk_widget_hide(pref->theme_label);
    gtk_widget_hide(pref->theme_switch);
    gtk_widget_hide(pref->s_notify_switch);
    gtk_widget_hide(pref->v_notify_switch);
    gtk_widget_hide(pref->e_notify_switch);
}
