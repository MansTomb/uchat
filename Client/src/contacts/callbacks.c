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
    t_info *info = user_data;

    gtk_tree_model_get_iter_from_string(model, &iter,
                                        gtk_tree_path_to_string(path));

    if (check_if_parent(tree_view, path))
        printf("est' child\n");
    else {
        printf("Nazata kolonka\n");
        // contacts->choosen_contact = iter; запомнить по итеру какой контакт выбор для коллбеков в меню
        gtk_menu_popup_at_pointer(GTK_MENU(info->windows->cont->menu), NULL);
    }
}

void mx_contacts_open_prof(GtkWidget *widget, gpointer data) {

}

void mx_contacts_send_message(GtkWidget *widget, gpointer data) {

}

void mx_contacts_block(GtkWidget *widget, gpointer data) {
    
}

void mx_contacts_delete(GtkWidget *widget, gpointer data) {
    // GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(contacts->treeview));

    // // check if this is a grp_name if it is make request to delete like a grp;
    // gtk_tree_store_remove(GTK_TREE_STORE(model), &contacts->choosen_contact);
}

// debug
static void printlist(t_list_node *node) {
    printf("%d  %s\n", ((t_user *)node->data)->id, ((t_user *)node->data)->login);
}

static void printlist2(t_list_node *node) {
    printf("gname -> %s\n", node->data);
}

void mx_on_add_contact(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    info->cl_data->tmp_users = mx_create_list();
    mx_get_list_users_json_wrapper(info);
    mx_foreach_list(info->cl_data->tmp_users, printlist);
    mx_foreach_list(info->cl_data->cont_grp_names, printlist2);
    mx_add_contact_build(info, info->windows->ac);
}

void mx_on_create_group(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_create_group_build(info, info->windows->cg);
}
