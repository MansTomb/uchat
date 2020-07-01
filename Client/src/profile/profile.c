#include "client.h"

static void labels(t_profile *profile, gboolean show) {
    if (show == TRUE) {
        gtk_widget_show(profile->namelb);
        gtk_widget_show(profile->fnamelb);
        gtk_widget_show(profile->snamelb);
        gtk_widget_show(profile->emaillb);
        gtk_widget_show(profile->statuslb);
    }
    else {
        gtk_widget_hide(profile->namelb);
        gtk_widget_hide(profile->fnamelb);
        gtk_widget_hide(profile->snamelb);
        gtk_widget_hide(profile->emaillb);
        gtk_widget_hide(profile->statuslb);
    }
}

void mx_profile_show(t_info *info) {
    t_profile *profile = info->windows->profile;

    if (profile == NULL)
        profile = info->windows->profile = mx_profile_constructor(info);

    info->current_window = info->windows->profile;

    // gtk_widget_show(profile->id);
    labels(profile, TRUE);
    gtk_widget_show(profile->name);
    gtk_widget_show(profile->fname);
    gtk_widget_show(profile->sname);
    gtk_widget_show(profile->email);
    gtk_widget_show(profile->status);
    gtk_widget_show(profile->scrollable);
    gtk_widget_show(profile->layout);
    gtk_widget_show(profile->edit);
}

void mx_profile_hide(t_info *info) {
    t_profile *profile = info->windows->profile;

    info->current_window = NULL;

    // gtk_widget_hide(profile->id);
    labels(profile, FALSE);
    gtk_widget_hide(profile->name);
    gtk_widget_hide(profile->fname);
    gtk_widget_hide(profile->sname);
    gtk_widget_hide(profile->email);
    gtk_widget_hide(profile->status);
    gtk_widget_hide(profile->scrollable);
    gtk_widget_hide(profile->layout);
    gtk_widget_hide(profile->edit);
}
