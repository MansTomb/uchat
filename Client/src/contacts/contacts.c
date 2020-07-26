#include "client.h"


void mx_contacts_build(t_info *info, t_contacts *cont) {
    if (cont == NULL)
        info->windows->cont = cont = malloc(sizeof(t_contacts));

    cont->builder = gtk_builder_new();
    gtk_builder_add_from_file(cont->builder, "./Resources/glade/contacts.glade", NULL);
    cont->box = mx_gobject_builder(cont->builder, "box");
    cont->addbt = mx_gobject_builder(cont->builder, "addbt");
    cont->crtbt = mx_gobject_builder(cont->builder, "crtbt");
    cont->tree_view = mx_gobject_builder(cont->builder, "view");
    cont->tree_store = GTK_TREE_STORE(gtk_builder_get_object(cont->builder, "contacts_tree"));
    cont->log_render = GTK_CELL_RENDERER(gtk_builder_get_object(cont->builder, "cr1"));
    cont->stat_render = GTK_CELL_RENDERER_PIXBUF(gtk_builder_get_object(cont->builder, "pr"));
    cont->log_col = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(cont->builder, "login_column"));
    cont->stat_col = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(cont->builder, "status"));
    cont->menu = mx_create_menu(info);
    cont->gmenu = mx_create_gmenu(info);
    cont->giters = mx_create_list();
    gtk_builder_connect_signals(cont->builder, info);

    gtk_tree_view_column_add_attribute(cont->log_col, cont->log_render, "text", 0);
    gtk_tree_view_column_add_attribute(cont->stat_col, GTK_CELL_RENDERER(cont->stat_render), "pixbuf", 1);

    mx_get_json_contacts(info);
    mx_create_table(info, cont);
    gtk_stack_add_titled(GTK_STACK(info->windows->ms->menu_stack), cont->box, "Contacts", "Contacts");
    gtk_widget_show(cont->box);
}

void mx_contacts_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->cont->box);
    free(info->windows->cont);
    info->windows->cont = NULL;
}
