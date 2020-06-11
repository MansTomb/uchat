#include "client.h"

void mx_find_and_hide_screen(t_info *info) {
    gpointer *window = info->current_window;
    t_windows *windows = info->windows;    

    if (window && window == (void *)windows->chat_switcher)
        mx_chat_switcher_hide(info);
    if (window && window == (void *)windows->contacts)
        mx_contacts_hide(info);
    if (window && window == (void *)windows->main_menu)
        mx_main_menu_hide(info);
    if (window && window == (void *)windows->reg)
        mx_register_screen_hide(info);
    if (window && window == (void *)windows->profile)
        mx_profile_hide(info);
}

void mx_main_menu_show(t_info *info) {
    t_main_menu *menu = info->windows->main_menu;

    if (menu == NULL)
        menu = info->windows->main_menu = mx_main_menu_constructor(info);

    gtk_widget_show(menu->box);
    gtk_widget_show(menu->profile);
    gtk_widget_show(menu->contancts);
    gtk_widget_show(menu->create_room);
    gtk_widget_show(menu->preferences);
    gtk_widget_show(menu->exit);
    gtk_widget_show(menu->back);
}

void mx_main_menu_hide(t_info *info) {
    t_main_menu *menu = info->windows->main_menu;

    gtk_widget_hide(menu->box);
    gtk_widget_hide(menu->profile);
    gtk_widget_hide(menu->contancts);
    gtk_widget_hide(menu->create_room);
    gtk_widget_hide(menu->preferences);
    gtk_widget_hide(menu->exit);
    gtk_widget_hide(menu->back);
}
