#include "client.h"

void mx_preferences_build(t_info *info, t_preferences *pref) {
    if (pref == NULL)
        info->windows->pref = pref = malloc(sizeof(t_preferences));

    pref->builder = gtk_builder_new();
    gtk_builder_add_from_file(pref->builder, "./Resources/glade/preferences.glade", NULL);

    pref->box = GTK_WIDGET(gtk_builder_get_object(pref->builder, "box"));
    pref->change_pass = GTK_WIDGET(gtk_builder_get_object(pref->builder, "change_pass"));
    pref->volume = GTK_WIDGET(gtk_builder_get_object(pref->builder, "volume"));
    pref->vnotify = GTK_WIDGET(gtk_builder_get_object(pref->builder, "vnotify"));
    pref->snotify = GTK_WIDGET(gtk_builder_get_object(pref->builder, "snotify"));
    pref->enotify = GTK_WIDGET(gtk_builder_get_object(pref->builder, "enotify"));
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
