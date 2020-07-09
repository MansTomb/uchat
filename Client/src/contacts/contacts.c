#include "client.h"

static void create_store(t_info *info, t_contacts *cont) {
    GtkTreeIter iter;
    GtkTreeIter iter_childs;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("./Resources/images/online.png", 20, 20, TRUE, NULL);
    GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_file_at_scale("./Resources/images/offline.png", 10, 10, TRUE, NULL);

    gtk_tree_view_column_add_attribute(cont->log_col, cont->log_render, "text", 0);
    gtk_tree_view_column_add_attribute(cont->stat_col, GTK_CELL_RENDERER(cont->stat_render), "pixbuf", 1);

    gtk_tree_store_append(cont->tree_store, &iter, NULL);
    gtk_tree_store_set(cont->tree_store, &iter, 0, "Друзья", -1);
    iter_childs = iter;
    gtk_tree_store_append(cont->tree_store, &iter, &iter_childs);
    gtk_tree_store_set(cont->tree_store, &iter, 0, "Heh", 1, pixbuf, -1);
    gtk_tree_store_append(cont->tree_store, &iter, NULL);
    gtk_tree_store_set(cont->tree_store, &iter, 0, "Не в группах", -1);
    iter_childs = iter;
    gtk_tree_store_append(cont->tree_store, &iter, &iter_childs);
    gtk_tree_store_set(cont->tree_store, &iter, 0, "hah", 1, pixbuf1, -1);
    gtk_tree_store_append(cont->tree_store, &iter, &iter_childs);
    gtk_tree_store_set(cont->tree_store, &iter, 0, "lohec", 1, pixbuf1, -1);
    gtk_tree_store_append(cont->tree_store, &iter, &iter_childs);
    gtk_tree_store_set(cont->tree_store, &iter, 0, "lya", 1, pixbuf, -1);
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
    gtk_builder_connect_signals(cont->builder, info);

    create_store(info, cont);
    gtk_stack_add_titled(GTK_STACK(info->windows->ms->menu_stack), cont->box, "Contacts", "Contacts");
    gtk_widget_show(cont->box);
}

void mx_contacts_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->cont->box);
    free(info->windows->cont);
    info->windows->cont = NULL;
}
