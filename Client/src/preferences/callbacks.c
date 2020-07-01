#include "client.h"

void mx_on_click_change_pass(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_change_pass_constructor(info);
}

void mx_on_click_theme_switch(GtkWidget *widget, gboolean state, gpointer data) {
    t_info *info = data;
    t_preferences *pref = info->windows->preferences;
    
    if (!state)
        mx_css_from_file(info, "./Resources/css/chat.css");
    else
        mx_css_from_file(info, "./Resources/css/chat_light.css");
    // send request to cange property at server and change it here if success
}

void mx_on_click_snoti_switch(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_preferences *pref = info->windows->preferences;
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
        // send request to cange property at server and change it here if success
        printf("Galo4ka stoit!");
    }
}

void mx_on_click_vnoti_switch(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_preferences *pref = info->windows->preferences;
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
        // send request to cange property at server and change it here if success
        printf("Galo4ka stoit!");
    }
}

void mx_on_click_enoti_switch(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_preferences *pref = info->windows->preferences;
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
        // send request to cange property at server and change it here if success
        printf("Galo4ka stoit!");
    }
}
