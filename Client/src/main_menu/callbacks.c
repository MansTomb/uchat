#include "client.h"

void mx_on_click_profile(GtkWidget *widget, gpointer data) {
    if(widget && data) {};
    t_info *info = data;

    mx_find_and_hide_screen(info);
    mx_profile_show(info);
}

void mx_on_click_contacts(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    
    mx_find_and_hide_screen(info);
    mx_contacts_show(info);
    if(widget && data) {};
}

void mx_on_click_create_room(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_room_creation_constructor(info);
    if(widget && data) {};
}

void mx_on_click_preferences(GtkWidget *widget, gpointer data) {
    if(widget && data) {};
}

void mx_on_click_exit(GtkWidget *widget, gpointer data) {
    mx_exit_constructor(data);
    if(widget && data) {};
}
