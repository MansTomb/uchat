#include "client.h"

static void create_store(t_info *info, t_contacts *cont) {
    GtkTreeIter iter;
    GtkTreeIter iter_childs;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("./Resources/images/online.png", 20, 20, TRUE, NULL);
    GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_file_at_scale("./Resources/images/offline.png", 10, 10, TRUE, NULL);

    gtk_tree_store_append(cont->tree_store, &iter, NULL);
    gtk_tree_store_set(cont->tree_store, &iter, 0, NULL, 1, "Друзья", -1);
    iter_childs = iter;
    gtk_tree_store_append(cont->tree_store, &iter, &iter_childs);
    gtk_tree_store_set(cont->tree_store, &iter, 0, "1", 1, "Heh", 2, pixbuf, -1);
    gtk_tree_store_append(cont->tree_store, &iter, NULL);
    gtk_tree_store_set(cont->tree_store, &iter, 0, NULL, 1, "Не в группах", -1);
    iter_childs = iter;
    gtk_tree_store_append(cont->tree_store, &iter, &iter_childs);
    gtk_tree_store_set(cont->tree_store, &iter, 0, "2", 1, "hah", 2, pixbuf1, -1);
    gtk_tree_store_append(cont->tree_store, &iter, &iter_childs);
    gtk_tree_store_set(cont->tree_store, &iter, 0, "3", 1, "lohec", 2, pixbuf1, -1);
    gtk_tree_store_append(cont->tree_store, &iter, &iter_childs);
    gtk_tree_store_set(cont->tree_store, &iter, 0, "4", 1, "lya", 2, pixbuf, -1);
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
