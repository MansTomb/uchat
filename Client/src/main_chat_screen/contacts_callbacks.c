#include "client.h"

static bool check_if_parent(GtkTreeView *tree_view, GtkTreePath *path) {
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);

    gtk_tree_model_get_iter_from_string(model, &iter,
                                        gtk_tree_path_to_string(path));
    if (gtk_tree_model_iter_has_child(model, &iter))
        return true;
    return false;
}

void mx_contacts_tree_on_click(GtkTreeView *tree_view, GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data) {
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);

    gtk_tree_model_get_iter_from_string(model, &iter,
                                        gtk_tree_path_to_string(path));

    if (check_if_parent(tree_view, path))
        printf("est' child\n");
    else {
        printf("Nazata kolonka\n");
        // contacts->choosen_contact = iter; запомнить по итеру какой контакт выбор для коллбеков в меню
    }
}

void mx_contacts_send_message(GtkWidget *widget, gpointer data) {

}

void mx_contacts_delete(GtkWidget *widget, gpointer data) {
    // GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(contacts->treeview));

    // // check if this is a grp_name if it is make request to delete like a grp;
    // gtk_tree_store_remove(GTK_TREE_STORE(model), &contacts->choosen_contact);
}
