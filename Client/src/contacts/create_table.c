#include "client.h"

static t_giter *giter_create(int id, char *gname, GtkTreeIter iter) {
    t_giter *new = malloc(sizeof(t_giter));

    new->gname = gname;
    new->id = id;
    new->iter = iter;

    return new;
}

static t_giter *get_giter_from_list_by_name(t_contacts *cont, int gid) {
    t_giter *iter = NULL;

    for (size_t i = 0; i < cont->giters->size; ++i) {
        iter = (mx_get_index(cont->giters, i))->data;

        if (iter->id == gid)
            return iter;
    }
    return iter;
}

static void push_contacts_with_group(t_info *info, t_contacts *cont,
                                     char *gname, int gid) {
    t_contact *contact = NULL;
    t_giter *iter = get_giter_from_list_by_name(cont, gid);
    GdkPixbuf *on = mx_get_image(MX_ONLINE, 20, 20);
    GdkPixbuf *off = mx_get_image(MX_OFFLINE, 10, 10);

    for (size_t i = 0; i < info->cl_data->contacts->size; ++i) {
        contact = (mx_get_index(info->cl_data->contacts, i))->data;

        if (contact->grp_id == iter->id) {
            gtk_tree_store_append(cont->tree_store, &cont->main_iter,
                                 &iter->iter);
            gtk_tree_store_set(cont->tree_store,
                               &cont->main_iter, 0,
                               contact->login, 1,
                               contact->active ? on : off, -1);
        }
    }
}

static void create_every_group(t_info *info, t_contacts *cont) {
    char *gname = NULL;
    int gid = 0;
    t_giter *giter = NULL;
    t_list *gnames = info->cl_data->cont_grp_names;

    for (size_t i = 0; i < gnames->size; ++i) {
        gname = ((t_group *)((mx_get_index(gnames, i))->data))->name;
        gid = ((t_group *)((mx_get_index(gnames, i))->data))->id;
        gtk_tree_store_append(cont->tree_store, &cont->main_iter, NULL);
        gtk_tree_store_set(cont->tree_store, &cont->main_iter, 0, gname, -1);
        giter = giter_create(gid, gname, cont->main_iter);
        mx_push_back(cont->giters, giter);
        push_contacts_with_group(info, cont, gname, gid);
    }
}

void mx_create_table(t_info *info, t_contacts *cont) {
    gtk_tree_store_clear(cont->tree_store);
    create_every_group(info, cont);
    while (cont->giters->size) {
        free(mx_get_index(cont->giters, 0)->data);
        mx_pop_index(cont->giters, 0);
    }
}
