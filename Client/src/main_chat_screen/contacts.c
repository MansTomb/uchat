#include "client.h"

static GtkTreeStore *create_store(t_info *info) {
    GtkTreeStore *tree_store;
    GtkTreeIter iter;
    GtkTreeIter iter_childs;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("./Resources/images/online.png", 20, 20, TRUE, NULL);
    GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_file_at_scale("./Resources/images/offline.png", 10, 10, TRUE, NULL);

    tree_store = gtk_tree_store_new(3, G_TYPE_STRING, G_TYPE_STRING, GDK_TYPE_PIXBUF);
    gtk_tree_store_append(tree_store, &iter, NULL);
    gtk_tree_store_set(tree_store, &iter, 0, NULL, 1, "Друзья", -1);
    iter_childs = iter;
    gtk_tree_store_append(tree_store, &iter, &iter_childs);
    gtk_tree_store_set(tree_store, &iter, 0, "1", 1, "Heh", 2, pixbuf, -1);
    gtk_tree_store_append(tree_store, &iter, NULL);
    gtk_tree_store_set(tree_store, &iter, 0, NULL, 1, "Не в группах", -1);
    iter_childs = iter;
    gtk_tree_store_append(tree_store, &iter, &iter_childs);
    gtk_tree_store_set(tree_store, &iter, 0, "2", 1, "hah", 2, pixbuf1, -1);
    gtk_tree_store_append(tree_store, &iter, &iter_childs);
    gtk_tree_store_set(tree_store, &iter, 0, "3", 1, "lohec", 2, pixbuf1, -1);
    gtk_tree_store_append(tree_store, &iter, &iter_childs);
    gtk_tree_store_set(tree_store, &iter, 0, "4", 1, "lya", 2, pixbuf, -1);

    return tree_store;
    if (info) {};
}

void mx_main_screen_contacts_create_tree(t_info *info) {

}
