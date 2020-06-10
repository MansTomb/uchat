#include "client.h"

static void attach_layout(t_info *info, t_main_menu *menu) {
    mx_layout_put(info->layout, menu->box, 10, 100);
    mx_layout_put(info->layout, menu->back, 10, 635);

    gtk_box_pack_start(GTK_BOX(menu->box), menu->profile, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(menu->box), menu->contancts, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(menu->box), menu->create_room, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(menu->box), menu->preferences, TRUE, FALSE, 1);
    gtk_box_pack_end(GTK_BOX(menu->box), menu->exit, TRUE, FALSE, 1);
}

static void attach_signals(t_info *info, t_main_menu *menu) {
    g_signal_connect(menu->profile, "clicked", G_CALLBACK(mx_on_click_profile), info);
    g_signal_connect(menu->contancts, "clicked", G_CALLBACK(mx_on_click_contacts), info);
    g_signal_connect(menu->create_room, "clicked", G_CALLBACK(mx_on_click_create_room), info);
    g_signal_connect(menu->preferences, "clicked", G_CALLBACK(mx_on_click_preferences), info);
    g_signal_connect(menu->exit, "clicked", G_CALLBACK(mx_on_click_exit), info);
    g_signal_connect(menu->back, "clicked", G_CALLBACK(mx_on_click_back), info);
}

static void set_preferences(t_main_menu *menu) {
    gtk_widget_set_size_request(menu->profile, 280, 50);
    gtk_widget_set_size_request(menu->contancts, 280, 50);
    gtk_widget_set_size_request(menu->create_room, 280, 50);
    gtk_widget_set_size_request(menu->preferences, 280, 50);
    gtk_widget_set_size_request(menu->exit, 280, 50);
    gtk_widget_set_size_request(menu->back, 280, 50);
}

t_main_menu *mx_main_menu_constructor(t_info *info) {
    t_main_menu *new = malloc(sizeof(t_main_menu));

    if (new && info) {
        new->box = mx_box_constructor("menu_box", 80, 40, GTK_ORIENTATION_VERTICAL);
        new->profile = mx_button_constuctor("Profile", "main_menu_buttons");
        new->contancts = mx_button_constuctor("Contacts", "main_menu_buttons");
        new->create_room = mx_button_constuctor("Create Room", "main_menu_buttons");
        new->preferences = mx_button_constuctor("Preferences", "main_menu_buttons");
        new->exit = mx_button_constuctor("Exit", "main_menu_buttons");
        new->back = mx_button_constuctor("Back", "main_menu_buttons");

        gtk_box_set_spacing(GTK_BOX(new->box), 1);

        attach_layout(info, new);
        attach_signals(info, new);
        set_preferences(new);
    }
    return new;
}
