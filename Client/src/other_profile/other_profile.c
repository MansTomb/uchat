#include "client.h"

// Сделать глейд надо

static void set_fields(t_info *info, t_other_profile *prof, t_contact *cont) {
    gtk_entry_set_text(GTK_ENTRY(prof->login), cont->login);
    gtk_entry_set_text(GTK_ENTRY(prof->fname), cont->f_name);
    gtk_entry_set_text(GTK_ENTRY(prof->lname), cont->s_name);
    gtk_entry_set_text(GTK_ENTRY(prof->email), cont->email);
}

static gboolean profile_destroy(GtkWidget *widget, GdkEvent *event, gpointer prof) {
    free(prof);
    
    return FALSE;
}

void mx_other_profile_build(t_info *info, t_contact *cont) {
    t_other_profile *prof = malloc(sizeof(t_other_profile));

    prof->builder = gtk_builder_new();
    gtk_builder_add_from_file(prof->builder, "./Resources/glade/other_user_profile.glade", NULL);

    prof->window = mx_gobject_builder(prof->builder, "window");
    prof->box = mx_gobject_builder(prof->builder, "profile");
    prof->image = mx_gobject_builder(prof->builder, "avatar");
    prof->login = mx_gobject_builder(prof->builder, "login");
    prof->fname = mx_gobject_builder(prof->builder, "fname");
    prof->lname = mx_gobject_builder(prof->builder, "lname");
    prof->email = mx_gobject_builder(prof->builder, "email");
    gtk_builder_connect_signals(prof->builder, prof);
    MX_GSIG_CON(prof->window, "delete-event", G_CALLBACK(profile_destroy), prof);

    set_fields(info, prof, cont);
    gtk_widget_show(prof->window);
}
