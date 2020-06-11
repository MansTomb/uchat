#include "client.h"

// gboolean foreach_func (GtkTreeModel *model,
//                 GtkTreePath  *path,
//                 GtkTreeIter  *iter,
//                 gpointer      user_data) {
//     gchar *id;
//     gchar *name;
//     gchar *tree_path_str;

//     /* Note: here we use 'iter' and not '&iter', because we did not allocate
//      *  the iter on the stack and are already getting the pointer to a tree iter */

//     gtk_tree_model_get (model, iter,
//                         0, &id,
//                         1, &name,
//                         -1);

//     tree_path_str = gtk_tree_path_to_string(path);

//     g_print ("Row %s: id: %s name: %s\n", tree_path_str,
//              id, name);

//     g_free(tree_path_str);

//     g_free(id); /* gtk_tree_model_get made copies of       */
//     g_free(name);  /* the strings for us when retrieving them */

//     if (user_data) {};
//     return FALSE; /* do not stop walking the store, call us with next row */
//   }

static GtkTreeStore *create_store(t_info *info) {
    GtkTreeStore *tree_store;
    GtkTreeIter iter;
    GtkTreeIter iter_childs;

    tree_store = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
        gtk_tree_store_append(tree_store, &iter, NULL);
        gtk_tree_store_set(tree_store, &iter, 0, NULL, 1, "Друзья", -1);
        iter_childs = iter;
        gtk_tree_store_append(tree_store, &iter, &iter_childs);
        gtk_tree_store_set(tree_store, &iter, 0, "1", 1, "Heh", -1);
        gtk_tree_store_append(tree_store, &iter, NULL);
        gtk_tree_store_set(tree_store, &iter, 0, NULL, 1, "Не в группах", -1);
        iter_childs = iter;
        gtk_tree_store_append(tree_store, &iter, &iter_childs);
        gtk_tree_store_set(tree_store, &iter, 0, "2", 1, "hah", -1);
        gtk_tree_store_append(tree_store, &iter, &iter_childs);
        gtk_tree_store_set(tree_store, &iter, 0, "3", 1, "lohec", -1);
        gtk_tree_store_append(tree_store, &iter, &iter_childs);
        gtk_tree_store_set(tree_store, &iter, 0, "4", 1, "lya", -1);
    
    return tree_store;
    if (info) {};
}

static void create_menu_items(t_contacts *contacts, GtkWidget *menu) {
    GtkWidget *items[2];

    items[0] = gtk_menu_item_new_with_label("Send message");
    items[1] = gtk_menu_item_new_with_label("Delete contact");

    gtk_menu_attach(GTK_MENU(menu), items[0], 0, 1, 0, 1);
    gtk_menu_attach(GTK_MENU(menu), items[1], 0, 1, 1, 2);

    gtk_widget_show(items[0]);
    gtk_widget_show(items[1]);

    g_signal_connect(items[0], "activate", G_CALLBACK(mx_contacts_send_message), contacts);
    g_signal_connect(items[1], "activate", G_CALLBACK(mx_contacts_delete), contacts);
}

static GtkWidget *create_menu(t_info *info) {
    GdkDisplay *display;
    GdkScreen *screen;
    GtkWidget *menu = gtk_menu_new();

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    if(info) {};
    gtk_menu_set_screen(GTK_MENU(menu), screen);
    return menu;
}

t_contacts *mx_contacts_constructor(t_info *info) {
    t_contacts *new = malloc(sizeof(t_contacts));
    GtkTreeStore *list_store;

    if (new) {
        list_store = create_store(info);
        new->treeview = mx_contacts_tree_constructor(info);
        new->addbt = mx_button_constuctor("Add Contact", "contacts_button_add");
        new->menu = create_menu(info);
        new->info = info;

        create_menu_items(new, new->menu);

        gtk_tree_view_set_model(GTK_TREE_VIEW(new->treeview), GTK_TREE_MODEL(list_store));

        g_signal_connect(new->treeview, "row-activated",
                                 G_CALLBACK(mx_contacts_tree_on_click), new);
        g_signal_connect(new->addbt, "clicked", G_CALLBACK(mx_conctacts_add_dialog), new);
        gtk_widget_set_size_request(new->addbt, 280, 50);
        mx_layout_put(info->layout, new->addbt, 700, 40);
        mx_layout_put(info->layout, new->treeview, 300, 100);
        // gtk_widget_show(new->treeview);
        // gtk_tree_model_foreach(GTK_TREE_MODEL(list_store), foreach_func, NULL);
    }
    return new;
}
