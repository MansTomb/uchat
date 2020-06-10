#include "client.h"

void mx_on_click_profile_edit(GtkWidget *widget, gpointer *data) {
    t_profile *profile = ((t_info *)data)->windows->profile;

    if (!gtk_editable_get_editable(GTK_EDITABLE(profile->name))) {
        gtk_editable_set_editable(GTK_EDITABLE(profile->name), TRUE);
        gtk_editable_set_editable(GTK_EDITABLE(profile->id), TRUE);
    }
    else {
        gtk_editable_set_editable(GTK_EDITABLE(profile->name), FALSE);
        gtk_editable_set_editable(GTK_EDITABLE(profile->id), FALSE);
    }

    if (widget) {};
    gtk_widget_hide(profile->edit);
    gtk_widget_show(profile->save);
    gtk_widget_show(profile->cancel);
}

void mx_on_click_profile_save(GtkWidget *widget, gpointer *data) {
    t_profile *profile = ((t_info *)data)->windows->profile;

    // Send data from server
    gtk_widget_hide(profile->save);
    gtk_widget_hide(profile->cancel);
    gtk_widget_show(profile->edit);
    if (widget) {};
}

void mx_on_click_profile_cancel(GtkWidget *widget, gpointer *data) {
    t_profile *profile = ((t_info *)data)->windows->profile;

    // Cancel changes data from server
    // Load data again
    gtk_widget_hide(profile->save);
    gtk_widget_hide(profile->cancel);
    gtk_widget_show(profile->edit);
    if (widget) {};
}
