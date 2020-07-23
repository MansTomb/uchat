#include "client.h"

static char *get_cname(GtkTreeModel *model, GtkTreeIter iter) {
    GValue value = G_VALUE_INIT;

    gtk_tree_model_get_value(model, &iter, 0, &value);
    
    return (char *)g_value_get_string(&value);
}

static gpointer get_status(GtkTreeModel *model, GtkTreeIter iter) {
    GValue value = G_VALUE_INIT;

    gtk_tree_model_get_value(model, &iter, 1, &value);
    
    return g_value_get_object(&value);
}

void mx_contacts_tree_on_click(GtkTreeView *tree_view, GtkTreePath *path,
                                GtkTreeViewColumn *column,
                                gpointer user_data) {
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    t_info *info = user_data;

    gtk_tree_model_get_iter_from_string(model, &iter,
                                        gtk_tree_path_to_string(path));

    if (!get_status(model, iter)) {
        info->windows->cont->clicked_cont = get_cname(model, iter);
        gtk_menu_popup_at_pointer(GTK_MENU(info->windows->cont->gmenu), NULL);
    }
    else {
        info->windows->cont->clicked_cont = get_cname(model, iter);
        gtk_menu_popup_at_pointer(GTK_MENU(info->windows->cont->menu), NULL);
    }
}

void mx_contacts_open_prof(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_contact *cont = NULL;

    for (size_t i = 0; i < info->cl_data->contacts->size; ++i) {
        cont = mx_get_index(info->cl_data->contacts, i)->data;
        if (strcmp(info->windows->cont->clicked_cont, cont->login) == 0) {
            mx_other_profile_build(info, cont);
            break;
        }
    }
}

void mx_contacts_send_message(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    mx_start_chat_json(info);
    printf("mx_contacts_send_message\n");
}

void mx_contacts_move(GtkWidget *widget, gpointer data) {
    printf("mx_contacts_move\n");
}

void mx_contacts_delete(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    // GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(contacts->treeview));
    printf("mx_contacts_delete\n");
    mx_del_cnt_json(info);
    // // check if this is a grp_name if it is, make request to delete like a grp;
    // gtk_tree_store_remove(GTK_TREE_STORE(model), &contacts->choosen_contact);
}

void mx_on_add_contact(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    info->cl_data->tmp_users = mx_create_list();
    mx_get_list_users_json_wrapper(info);
    mx_add_contact_build(info, info->windows->ac);
}

void mx_on_create_group(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_create_group_build(info, info->windows->cg);
}
