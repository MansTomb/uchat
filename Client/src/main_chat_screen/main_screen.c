#include "client.h"

void mx_main_screen_build(t_info *info, t_main_screen *ms) {
    if (ms == NULL)
        info->windows->ms = ms = malloc(sizeof(t_main_screen));

    ms->builder = gtk_builder_new();
    gtk_builder_add_from_file(ms->builder, "./Resources/glade/main_chat_screen.glade", NULL);

    ms->window = GTK_WIDGET(gtk_builder_get_object(ms->builder, "main_window"));
    ms->revealer = GTK_WIDGET(gtk_builder_get_object(ms->builder, "revealer"));
    ms->chat_stack = GTK_WIDGET(gtk_builder_get_object(ms->builder, "chat_stack"));
    ms->menu_stack = GTK_WIDGET(gtk_builder_get_object(ms->builder, "menu_stack"));
    gtk_builder_connect_signals(ms->builder, info);

    mx_chat_put(info, "Pervii", 1);
    mx_chat_put(info, "Vtoroi", 2);
    mx_profile_build(info, info->windows->prof);
    mx_preferences_build(info, info->windows->pref);
    mx_contacts_build(info, info->windows->cont);
    mx_set_vnoti(ms, "Vtoroi", 1);
    MX_GSIG_CON(ms->window, "delete-event", G_CALLBACK(mx_destroy), info);
    mx_css_from_file(info, "./Resources/css/main.css");
    gtk_widget_show(ms->window);
}

void mx_main_screen_destroy(t_info *info) {
    info->wchange = 1;
    gtk_widget_destroy(info->windows->ms->window);
    free(info->windows->ms);
    info->windows->ms = NULL;
    info->wchange = 0;
}

void mx_on_click_main_menu(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    gboolean revealed = gtk_revealer_get_reveal_child(GTK_REVEALER(info->windows->ms->revealer));

    gtk_revealer_set_reveal_child(GTK_REVEALER(info->windows->ms->revealer), !revealed);
}

void mx_on_click_room_creation(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_room_creation_build(info, info->windows->rc);
}

void mx_on_click_exit(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    gtk_main_quit();
}
