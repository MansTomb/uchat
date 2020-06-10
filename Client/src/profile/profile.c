#include "client.h"

void mx_profile_show(t_info *info) {
    t_profile *profile = info->windows->profile;

    if (profile == NULL)
        profile = info->windows->profile = mx_profile_constructor(info);

    info->current_window = info->windows->profile;

    gtk_widget_show(profile->id);
    gtk_widget_show(profile->idlabel);
    gtk_widget_show(profile->name);
    gtk_widget_show(profile->namelabel);
    gtk_widget_show(profile->scrollable);
    gtk_widget_show(profile->layout);
    gtk_widget_show(profile->edit);
}

void mx_profile_hide(t_info *info) {
    t_profile *profile = info->windows->profile;

    info->current_window = NULL;

    gtk_widget_hide(profile->id);
    gtk_widget_hide(profile->idlabel);
    gtk_widget_hide(profile->name);
    gtk_widget_hide(profile->namelabel);
    gtk_widget_hide(profile->scrollable);
    gtk_widget_hide(profile->layout);
    gtk_widget_hide(profile->edit);
    gtk_widget_hide(profile->cancel);
    gtk_widget_hide(profile->save);
}
