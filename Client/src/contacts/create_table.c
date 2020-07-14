#include "client.h"

static t_giter *giter_create(char *gname, GtkTreeIter iter) {
    t_giter *new = malloc(sizeof(t_giter));

    new->gname = gname;
    new->iter = iter;

    return new;
}

static t_giter *get_giter_from_list_by_name(t_contacts *cont, char *gname) {
    t_giter *iter = NULL;

    for (size_t i = 0; i < cont->giters->size; ++i) {
        iter = (mx_get_index(cont->giters, i))->data;

        if (strcmp(iter->gname, gname) == 0)
            return iter;
    }
    return iter;
}

static void push_contacts_with_group(t_info *info, t_contacts *cont, char *gname) {
    t_contact *contact = NULL;
    t_giter *iter = get_giter_from_list_by_name(cont, gname);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("./Resources/images/online.png", 20, 20, TRUE, NULL);
    GdkPixbuf *pixbuf1 = gdk_pixbuf_new_from_file_at_scale("./Resources/images/offline.png", 10, 10, TRUE, NULL);

    for (size_t i = 0; i < info->cl_data->contacts->size; ++i) {
        contact = (mx_get_index(info->cl_data->contacts, i))->data;

        gtk_tree_store_append(cont->tree_store, &cont->main_iter, &iter->iter);
        gtk_tree_store_set(cont->tree_store, &cont->main_iter, 0, contact->login, 1, pixbuf, -1);
    }
}

static void create_every_group(t_info *info, t_contacts *cont) {
    char *grpname = NULL;

    for (size_t i = 0; i < info->cl_data->cont_grp_names->size; ++i) {
        grpname = (mx_get_index(info->cl_data->cont_grp_names, i))->data;
        gtk_tree_store_append(cont->tree_store, &cont->main_iter, NULL);
        gtk_tree_store_set(cont->tree_store, &cont->main_iter, 0, grpname, -1);
        mx_push_back(cont->giters, giter_create(grpname, cont->main_iter));
        push_contacts_with_group(info, cont, grpname);
    }
}

void mx_create_table(t_info *info, t_contacts *cont) {
    gtk_tree_store_clear(cont->tree_store);
    mx_clear_list(cont->giters);
    create_every_group(info, cont);
}
