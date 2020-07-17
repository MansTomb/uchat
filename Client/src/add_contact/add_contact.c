#include "client.h"

static void set_group_names(t_contact_add *ac) {
    t_list *grp_list = ac->info->cl_data->cont_grp_names;
    char *tmp = NULL;

    for (size_t i = 0; i < grp_list->size; ++i) {
        tmp = mx_get_index(grp_list, i)->data;
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(ac->combobox), tmp);
    }
}

static void set_search_completetion(t_contact_add *ac) {
    t_list *tmp = ac->info->cl_data->tmp_users;
    GtkTreeIter iter;
    t_user *name = NULL;

    for (size_t i = 0; i < tmp->size; ++i) {
        name = mx_get_index(tmp, i)->data;
        gtk_tree_store_append(ac->nameslist, &iter, NULL);
        gtk_tree_store_set(ac->nameslist, &iter, 0, name->login, -1);
    }
}

void mx_add_contact_build(t_info *info, t_contact_add *ac) {
    if (ac == NULL)
        info->windows->ac = ac = malloc(sizeof(t_contact_add));

    ac->builder = gtk_builder_new();
    gtk_builder_add_from_file(ac->builder, "./Resources/glade/add_contact.glade", NULL);

    ac->dialog = GTK_WIDGET(gtk_builder_get_object(ac->builder, "dialog"));
    ac->addbt = GTK_WIDGET(gtk_builder_get_object(ac->builder, "add"));
    ac->cancelbt = GTK_WIDGET(gtk_builder_get_object(ac->builder, "cancel"));
    ac->entry = GTK_WIDGET(gtk_builder_get_object(ac->builder, "entry"));
    ac->combobox = GTK_WIDGET(gtk_builder_get_object(ac->builder, "combobox"));
    ac->nameslist = GTK_TREE_STORE(gtk_builder_get_object(ac->builder, "names"));
    ac->e_comp = GTK_ENTRY_COMPLETION(gtk_builder_get_object(ac->builder, "e_comp"));
    gtk_builder_connect_signals(ac->builder, ac);

    gtk_entry_set_completion(GTK_ENTRY(ac->entry), ac->e_comp);
    ac->info = info;
    set_search_completetion(ac);
    set_group_names(ac);

    gtk_widget_show(ac->dialog);
}

void mx_add_contact_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->ac->dialog);
    free(info->windows->ac);
    info->windows->ac = NULL;
}
