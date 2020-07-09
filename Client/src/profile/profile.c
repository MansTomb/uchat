#include "client.h"

static void set_fields(t_info *info, t_profile *prof) {
    t_profile_data *data = info->cl_data->profile;

    gtk_entry_set_text(GTK_ENTRY(prof->login), data->login);
    gtk_entry_set_text(GTK_ENTRY(prof->fname), data->first_name);
    gtk_entry_set_text(GTK_ENTRY(prof->lname), data->sec_name);
    gtk_entry_set_text(GTK_ENTRY(prof->email), data->user_email);
}

void mx_profile_build(t_info *info, t_profile *prof) {
    if (prof == NULL)
        info->windows->prof = prof = malloc(sizeof(t_profile));

    prof->builder = gtk_builder_new();
    gtk_builder_add_from_file(prof->builder, "./Resources/glade/profile.glade", NULL);

    prof->box = GTK_WIDGET(gtk_builder_get_object(prof->builder, "profile"));
    prof->image = GTK_WIDGET(gtk_builder_get_object(prof->builder, "avatar"));
    prof->avatartbt = GTK_WIDGET(gtk_builder_get_object(prof->builder, "avatarbt"));
    prof->save = GTK_WIDGET(gtk_builder_get_object(prof->builder, "save"));
    prof->edit = GTK_WIDGET(gtk_builder_get_object(prof->builder, "edit"));
    prof->cancel = GTK_WIDGET(gtk_builder_get_object(prof->builder, "cancel"));
    prof->login = GTK_WIDGET(gtk_builder_get_object(prof->builder, "login"));
    prof->fname = GTK_WIDGET(gtk_builder_get_object(prof->builder, "fname"));
    prof->lname = GTK_WIDGET(gtk_builder_get_object(prof->builder, "lname"));
    prof->email = GTK_WIDGET(gtk_builder_get_object(prof->builder, "email"));
    gtk_builder_connect_signals(prof->builder, info);

    set_fields(info, prof);
    gtk_stack_add_titled(GTK_STACK(info->windows->ms->menu_stack), prof->box, "Profile", "Profile");
    gtk_widget_hide(prof->cancel);
    gtk_widget_hide(prof->save);
    gtk_widget_show(prof->box);
}

void mx_profile_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->prof->box);
    free(info->windows->prof);
    info->windows->prof = NULL;
}
