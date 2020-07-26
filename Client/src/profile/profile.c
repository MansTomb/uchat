#include "client.h"

static void set_fields(t_info *info, t_profile *prof) {
    t_profile_data *data = info->cl_data->profile;

    gtk_entry_set_text(GTK_ENTRY(prof->login), data->login);
    gtk_entry_set_text(GTK_ENTRY(prof->fname), data->first_name);
    gtk_entry_set_text(GTK_ENTRY(prof->lname), data->sec_name);
    gtk_entry_set_text(GTK_ENTRY(prof->email), data->user_email);
}

static void set_preferences(t_info *info, t_profile *prof) {
    gtk_stack_add_titled(GTK_STACK(info->windows->ms->menu_stack),
                                             prof->box, "Profile", "Profile");
    gtk_widget_hide(prof->cancel);
    gtk_widget_hide(prof->save);
    gtk_widget_show(prof->box);
}

void mx_profile_build(t_info *info, t_profile *prof) {
    if (prof == NULL)
        info->windows->prof = prof = malloc(sizeof(t_profile));

    prof->builder = gtk_builder_new();
    gtk_builder_add_from_file(prof->builder, MX_GLADE_PROF, NULL);
    prof->box = mx_gobject_builder(prof->builder, "profile");
    prof->image = mx_gobject_builder(prof->builder, "avatar");
    prof->avatartbt = mx_gobject_builder(prof->builder, "avatarbt");
    prof->save = mx_gobject_builder(prof->builder, "save");
    prof->edit = mx_gobject_builder(prof->builder, "edit");
    prof->cancel = mx_gobject_builder(prof->builder, "cancel");
    prof->login = mx_gobject_builder(prof->builder, "login");
    prof->fname = mx_gobject_builder(prof->builder, "fname");
    prof->lname = mx_gobject_builder(prof->builder, "lname");
    prof->email = mx_gobject_builder(prof->builder, "email");
    gtk_builder_connect_signals(prof->builder, info);
    set_fields(info, prof);
    set_preferences(info, prof);
}

void mx_profile_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->prof->box);
    free(info->windows->prof);
    info->windows->prof = NULL;
}
