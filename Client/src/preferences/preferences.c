#include "client.h"

void mx_preferences_build(t_info *info, t_preferences *pref) {
    if (pref == NULL)
        info->windows->pref = pref = malloc(sizeof(t_preferences));

    pref->builder = gtk_builder_new();
    gtk_builder_add_from_file(pref->builder, "./Resources/glade/preferences.glade", NULL);

    pref->box = mx_gobject_builder(pref->builder, "box");
    pref->change_pass = mx_gobject_builder(pref->builder, "change_pass");
    pref->del_prof = mx_gobject_builder(pref->builder, "delete_profile");
    pref->themeswitch = mx_gobject_builder(pref->builder, "theme_switcher");
    pref->volume = mx_gobject_builder(pref->builder, "volume");
    pref->vnotify = mx_gobject_builder(pref->builder, "vnotify");
    pref->snotify = mx_gobject_builder(pref->builder, "snotify");
    pref->enotify = mx_gobject_builder(pref->builder, "enotify");
    gtk_builder_connect_signals(pref->builder, info);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pref->vnotify), info->cl_data->profile->vs_noty);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pref->snotify), info->cl_data->profile->sound_noty);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pref->enotify), info->cl_data->profile->email_noty);

    gtk_stack_add_titled(GTK_STACK(info->windows->ms->menu_stack), pref->box, "Preferences", "Preferences");
    gtk_widget_show(pref->box);
}

void mx_preferences_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->pref->box);
    free(info->windows->pref);
    info->windows->pref = NULL;
}
