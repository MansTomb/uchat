#include "client.h"

static void attach_layout(t_info *info, t_main_menu *menu) {
    mx_layout_put(info->layout, menu->box, 10, 100);
    mx_layout_put(info->layout, menu->exit, 10, 635);

    gtk_box_pack_start(GTK_BOX(menu->box), menu->profile, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(menu->box), menu->contancts, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(menu->box), menu->create_room, TRUE, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(menu->box), menu->preferences, TRUE, FALSE, 1);
    gtk_box_pack_end(GTK_BOX(menu->box), menu->back, TRUE, FALSE, 1);
}

static void attach_signals(t_info *info, t_main_menu *menu) {
    MX_GSIG_CON(menu->profile, "clicked", MX_CB(mx_on_click_profile), info);
    MX_GSIG_CON(menu->contancts, "clicked", MX_CB(mx_on_click_contacts), info);
    MX_GSIG_CON(menu->create_room, "clicked", MX_CB(mx_on_click_create_room), info);
    MX_GSIG_CON(menu->preferences, "clicked", MX_CB(mx_on_click_preferences), info);
    MX_GSIG_CON(menu->exit, "clicked", MX_CB(mx_on_click_exit), info);
    MX_GSIG_CON(menu->back, "clicked", MX_CB(mx_on_click_back), info);
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
        new->box = mx_box_constructor("menu_box", 80, 40, MX_BOX_V);
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
