#include "client.h"

void mx_on_click_profile(GtkWidget *widget, gpointer data) {
    if(widget && data) {};
    t_info *info = data;

    mx_chat_switcher_hide(info);
    mx_profile_show(info);
}

void mx_on_click_contacts(GtkWidget *widget, gpointer data) {
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
    if(widget && data) {};
}
