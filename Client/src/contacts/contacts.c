#include "client.h"

static void create_menu_items(t_contacts *contacts, GtkWidget *menu) {
    GtkWidget *items[4];

    items[0] = gtk_menu_item_new_with_label("User profile");
    items[1] = gtk_menu_item_new_with_label("Send message");
    items[2] = gtk_menu_item_new_with_label("Block contact");
    items[3] = gtk_menu_item_new_with_label("Delete contact");

    gtk_menu_attach(GTK_MENU(menu), items[0], 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(menu), items[1], 0, 1, 1, 2);
    gtk_menu_attach(GTK_MENU(menu), items[2], 0, 1, 2, 3);
    gtk_menu_attach(GTK_MENU(menu), items[3], 0, 1, 3, 4);

    gtk_widget_show(items[0]);
    gtk_widget_show(items[1]);
    gtk_widget_show(items[2]);
    gtk_widget_show(items[3]);

    MX_GSIG_CON(items[0], "activate", MX_CB(mx_contacts_open_prof), contacts);
    MX_GSIG_CON(items[1], "activate", MX_CB(mx_contacts_send_message), contacts);
    MX_GSIG_CON(items[2], "activate", MX_CB(mx_contacts_block), contacts);
    MX_GSIG_CON(items[2], "activate", MX_CB(mx_contacts_delete), contacts);
}

static GtkWidget *create_menu(t_info *info) {
    GdkDisplay *display;
    GdkScreen *screen;
    GtkWidget *menu = gtk_menu_new();

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_menu_set_screen(GTK_MENU(menu), screen);
    create_menu_items(info->windows->cont, menu);
    return menu;
}

void mx_contacts_build(t_info *info, t_contacts *cont) {
    if (cont == NULL)
        info->windows->cont = cont = malloc(sizeof(t_contacts));

    cont->builder = gtk_builder_new();
    gtk_builder_add_from_file(cont->builder, "./Resources/glade/contacts.glade", NULL);

    cont->box = GTK_WIDGET(gtk_builder_get_object(cont->builder, "box"));
    cont->addbt = GTK_WIDGET(gtk_builder_get_object(cont->builder, "addbt"));
    cont->crtbt = GTK_WIDGET(gtk_builder_get_object(cont->builder, "crtbt"));
    cont->tree_view = GTK_WIDGET(gtk_builder_get_object(cont->builder, "view"));
    cont->tree_store = GTK_TREE_STORE(gtk_builder_get_object(cont->builder, "contacts_tree"));
    cont->log_render = GTK_CELL_RENDERER(gtk_builder_get_object(cont->builder, "cr1"));
    cont->stat_render = GTK_CELL_RENDERER_PIXBUF(gtk_builder_get_object(cont->builder, "pr"));
    cont->log_col = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(cont->builder, "login_column"));
    cont->stat_col = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(cont->builder, "status"));
    cont->menu = create_menu(info);
    gtk_builder_connect_signals(cont->builder, info);

    mx_create_table(info, cont);
    gtk_stack_add_titled(GTK_STACK(info->windows->ms->menu_stack), cont->box, "Contacts", "Contacts");
    gtk_widget_show(cont->box);
}

void mx_contacts_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->cont->box);
    free(info->windows->cont);
    info->windows->cont = NULL;
}
