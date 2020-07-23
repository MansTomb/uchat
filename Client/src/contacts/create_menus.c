#include "client.h"

static void create_menu_items(GtkWidget *menu, t_info *info) {
    GtkWidget *items[4];

    items[0] = gtk_menu_item_new_with_label("User profile");
    items[1] = gtk_menu_item_new_with_label("Send message");
    items[2] = gtk_menu_item_new_with_label("Move contact");
    items[3] = gtk_menu_item_new_with_label("Delete contact");

    gtk_menu_attach(GTK_MENU(menu), items[0], 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(menu), items[1], 0, 1, 1, 2);
    gtk_menu_attach(GTK_MENU(menu), items[2], 0, 1, 2, 3);
    gtk_menu_attach(GTK_MENU(menu), items[3], 0, 1, 3, 4);

    gtk_widget_show(items[0]);
    gtk_widget_show(items[1]);
    gtk_widget_show(items[2]);
    gtk_widget_show(items[3]);

    MX_GSIG_CON(items[0], "activate", MX_CB(mx_contacts_open_prof), info);
    MX_GSIG_CON(items[1], "activate", MX_CB(mx_contacts_send_message), info);
    MX_GSIG_CON(items[2], "activate", MX_CB(mx_contacts_move), info);
    MX_GSIG_CON(items[3], "activate", MX_CB(mx_contacts_delete), info);
}

static void create_gmenu_items(GtkWidget *menu, t_info *info) {
    GtkWidget *item = NULL;

    item = gtk_menu_item_new_with_label("Delete Group");

    gtk_menu_attach(GTK_MENU(menu), item, 0, 1, 0, 1);

    gtk_widget_show(item);

    MX_GSIG_CON(item, "activate", MX_CB(mx_contacts_delete), info);
}

GtkWidget *mx_create_menu(t_info *info) {
    GdkDisplay *display;
    GdkScreen *screen;
    GtkWidget *menu = gtk_menu_new();
    GtkWidget *tv = info->windows->cont->tree_view;

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_menu_set_screen(GTK_MENU(menu), screen);
    create_menu_items(menu, info);
    MX_GSIG_CON(tv, "row-activated", MX_CB(mx_contacts_tree_on_click), info);
    return menu;
}

GtkWidget *mx_create_gmenu(t_info *info) {
    GdkDisplay *display;
    GdkScreen *screen;
    GtkWidget *menu = gtk_menu_new();
    GtkWidget *tv = info->windows->cont->tree_view;

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_menu_set_screen(GTK_MENU(menu), screen);
    create_gmenu_items(menu, info);
    return menu;
}
