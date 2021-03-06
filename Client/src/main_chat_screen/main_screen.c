#include "client.h"

void mx_main_screen_build(t_info *info, t_main_screen *ms) {
    if (ms == NULL)
        info->windows->ms = ms = malloc(sizeof(t_main_screen));

    ms->builder = gtk_builder_new();
    gtk_builder_add_from_file(ms->builder, MX_GLADE_MS, NULL);

    ms->window = mx_gobject_builder(ms->builder, "main_window");
    ms->revealer = mx_gobject_builder(ms->builder, "revealer");
    ms->chat_stack = mx_gobject_builder(ms->builder, "chat_stack");
    ms->menu_stack = mx_gobject_builder(ms->builder, "menu_stack");
    gtk_builder_connect_signals(ms->builder, info);
    mx_profile_build(info, info->windows->prof);
    mx_preferences_build(info, info->windows->pref);
    mx_contacts_build(info, info->windows->cont);
    mx_get_json_chats_list(info);
    MX_GSIG_CON(ms->window, "delete-event", G_CALLBACK(mx_destroy), info);
    mx_css_from_file(info, "./Resources/css/chat_light.css");
    gtk_widget_show(ms->window);
}

void mx_main_screen_destroy(t_info *info) {
    info->wchange = 1;
    mx_contacts_destroy(info);
    mx_profile_destroy(info);
    mx_preferences_destroy(info);
    gtk_widget_destroy(info->windows->ms->window);
    free(info->windows->ms);
    info->windows->ms = NULL;
    info->wchange = 0;
}

void mx_on_click_main_menu(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    gboolean revealed = gtk_revealer_get_reveal_child(
                                    GTK_REVEALER(info->windows->ms->revealer));

    gtk_revealer_set_reveal_child(GTK_REVEALER(info->windows->ms->revealer),
                                                                 !revealed);
}

void mx_on_click_room_creation(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_room_creation_build(info, info->windows->rc);
}

void mx_on_click_exit(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_destroy(NULL, NULL, info);
}
