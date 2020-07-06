#include "client.h"

void mx_main_screen_build(t_info *info, t_main_screen *ms) {
    if (ms == NULL)
        info->windows->ms = ms = malloc(sizeof(t_main_screen));

    ms->builder = gtk_builder_new();
    gtk_builder_add_from_file(ms->builder, "./Resources/glade/main_chat_screen.glade", NULL);

    ms->window = GTK_WIDGET(gtk_builder_get_object(ms->builder, "main_window"));
    ms->revealer = GTK_WIDGET(gtk_builder_get_object(ms->builder, "revealer"));
    ms->chat_stack = GTK_WIDGET(gtk_builder_get_object(ms->builder, "chat_stack"));
    gtk_builder_connect_signals(ms->builder, info);

    gtk_widget_show(ms->window);
}

void mx_main_screen_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->ms->window);
    free(info->windows->ms);
    info->windows->ms = NULL;
}

void mx_on_click_main_menu(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    gboolean revealed = gtk_revealer_get_reveal_child(GTK_REVEALER(info->windows->ms->revealer));

    gtk_revealer_set_reveal_child(GTK_REVEALER(info->windows->ms->revealer), !revealed);
}

void mx_on_click_room_creation(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_room_creation_build(info, info->windows->rc);
}

void mx_on_click_exit(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    gtk_main_quit();
}

void mx_on_add_contact(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_add_contact_build(info, info->windows->ac);
}

void mx_on_create_group(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_create_group_build(info, info->windows->cg);
}

static void set_editables(t_profile *profile, gboolean is_editable) {
    // gtk_editable_set_editable(GTK_EDITABLE(profile->name), is_editable);
    // gtk_editable_set_editable(GTK_EDITABLE(profile->fname), is_editable);
    // gtk_editable_set_editable(GTK_EDITABLE(profile->sname), is_editable);
    // gtk_editable_set_editable(GTK_EDITABLE(profile->email), is_editable);
    // gtk_editable_set_editable(GTK_EDITABLE(profile->status), is_editable);
    // gtk_entry_set_has_frame(GTK_ENTRY(profile->name), is_editable);
    // gtk_entry_set_has_frame(GTK_ENTRY(profile->fname), is_editable);
    // gtk_entry_set_has_frame(GTK_ENTRY(profile->sname), is_editable);
    // gtk_entry_set_has_frame(GTK_ENTRY(profile->email), is_editable);
    // gtk_entry_set_has_frame(GTK_ENTRY(profile->status), is_editable);
}

void mx_on_click_profile_edit(GtkWidget *widget, gpointer *data) {
    // t_profile *profile = ((t_info *)data)->windows->profile;

    // set_editables(profile, TRUE);

    // gtk_widget_hide(profile->edit);
    // gtk_widget_show(profile->save);
    // gtk_widget_show(profile->cancel);
}

void mx_on_click_profile_save(GtkWidget *widget, gpointer *data) {
    // t_profile *profile = ((t_info *)data)->windows->profile;

    // mx_upd_prof_build_json_wrapper((t_info *)data);
    // // Send data to server mx_make_update_profile estimated return mx_success_update_profile
    // set_editables(profile, FALSE);
    // gtk_widget_hide(profile->save);
    // gtk_widget_hide(profile->cancel);
    // gtk_widget_show(profile->edit);
}

void mx_on_click_profile_cancel(GtkWidget *widget, gpointer *data) {
    // t_profile *profile = ((t_info *)data)->windows->profile;

    // // Cancel changes data from server
    // // Load data again, data must be stored at profile structure
    // set_editables(profile, FALSE);
    // gtk_widget_hide(profile->save);
    // gtk_widget_hide(profile->cancel);
    // gtk_widget_show(profile->edit);
}

static void upd_prof_bld_json(const t_info *info, int *s_sock) {
    cJSON *jprof = cJSON_CreateObject();
    // const t_profile *new_prof = info->windows->profile;
    char *str = NULL;

    cJSON_AddNumberToObject(jprof, "json_type", make_update_profile);
    cJSON_AddNumberToObject(jprof, "uid", info->cl_data->profile->id);
    cJSON_AddStringToObject(jprof, "fname", "");
    cJSON_AddStringToObject(jprof, "sname", "");
    cJSON_AddStringToObject(jprof, "email", "");
    cJSON_AddStringToObject(jprof, "status", "");
    cJSON_AddNumberToObject(jprof, "snot", 0);
    cJSON_AddNumberToObject(jprof, "vnot", 0);
    cJSON_AddNumberToObject(jprof, "enot", 0);

    str = cJSON_Print(jprof);
    if (!str || send(*s_sock, str, strlen(str), 0) == -1)
        fprintf(stderr, "make update profile: 'send' error occured\n");
    cJSON_Delete(jprof);
    if (MX_MALLOC_SIZE(str))
        free(str);
}

// void upd_profile(t_info *info) {
//     t_profile_data *prof = info->cl_data->profile;
//     char *p_id = mx_lltoa(prof->id);

//     mx_save_login_data(info);
//     gtk_entry_set_text(GTK_ENTRY(info->windows->profile->name), p_id);
//     gtk_entry_set_text(GTK_ENTRY(info->windows->profile->id), prof->first_name);
//     free(p_id);
// }

void mx_upd_prof_build_json_wrapper(t_info *info) {
    upd_prof_bld_json(info, &info->sock->sock);
    mx_wait_for_json(info, success_update_profile, success_update_profile);
    // upd_profile(info);
}

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
    t_contacts *contacts = user_data;

    gtk_tree_model_get_iter_from_string(model, &iter,
                                        gtk_tree_path_to_string(path));

    if (check_if_parent(tree_view, path))
        printf("est' child\n");
    else {
        printf("Nazata kolonka\n");
        contacts->choosen_contact = iter;
        gtk_menu_popup_at_pointer(GTK_MENU(contacts->menu), NULL);
    }
}

void mx_contacts_send_message(GtkWidget *widget, gpointer data) {

}

void mx_contacts_delete(GtkWidget *widget, gpointer data) {
    t_contacts *contacts = data;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(contacts->treeview));

    // check if this is a grp_name if it is make request to delete like a grp;
    gtk_tree_store_remove(GTK_TREE_STORE(model), &contacts->choosen_contact);
}

static void free_wrapper(char **str, cJSON **jobj) {
    cJSON_Delete(*jobj);
    if (MX_MALLOC_SIZE(str))
        free(*str);
}

static void send_contacts_request(t_info *info) {
    cJSON *jobj = cJSON_CreateObject();
    char *str = NULL;

    cJSON_AddNumberToObject(jobj, "json_type", get_client_contacts);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id); // we need to send our client uid

    str = cJSON_Print(jobj);
    if (!str || send(info->sock->sock, str, strlen(str), 0) == -1)
        fprintf(stderr, "get client contacts: 'send' error occured\n");
    free_wrapper(&str, &jobj);
}

t_contact *mx_contact_constructor(cJSON **jc) {
    t_contact *c = (t_contact *)malloc(sizeof(t_contact));

    c->cid = cJSON_GetObjectItem(*jc, "contact_id")->valueint;
    c->login = cJSON_GetObjectItem(*jc, "login")->valuestring;
    c->f_name = cJSON_GetObjectItem(*jc, "first_name")->valuestring;
    c->s_name = cJSON_GetObjectItem(*jc, "second_name")->valuestring;
    c->email = cJSON_GetObjectItem(*jc, "email")->valuestring;
    c->stat = cJSON_GetObjectItem(*jc, "status")->valuestring;
    c->grp_id = cJSON_GetObjectItem(*jc, "group_id")->valueint;
    c->grp_name = cJSON_GetObjectItem(*jc, "group_name")->valuestring;
    return c;
}

// TODO save_contacts (parse array from json and asve it into list)
void save_contacts(t_info *info) {
    for (int i = 0; i < cJSON_GetArraySize(cJSON_GetObjectItem(info->json, "contacts")); ++i) {
        cJSON *contacts = cJSON_GetArrayItem(cJSON_GetObjectItem(info->json, "contacts"), i);
        mx_push_back(info->cl_data->contacts, mx_contact_constructor(&contacts));
        free(contacts); // может надо а может и не надо
    }
}

void mx_get_json_contact(t_info *info) {
    send_contacts_request(info);
    mx_wait_for_json(info, send_client_contacts, send_client_contacts);
    save_contacts(info);
}

static void add_bld_json(const char *id, const char *log_to_srv, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();
    char *str = NULL;

    cJSON_AddNumberToObject(jlogin, "json_type", make_add_new_contact);
    cJSON_AddStringToObject(jlogin, "client_id", id);
    cJSON_AddStringToObject(jlogin, "log_to_srv", log_to_srv);

    str = cJSON_Print(jlogin);
    if (!str || send(s_sock, str, strlen(str), 0) == -1)
        fprintf(stderr, "make add new contact: 'send' error occured\n");
    cJSON_Delete(jlogin);
    if (MX_MALLOC_SIZE(str))
        free(str);
}

void mx_add_contact_build_json_wrapper(t_contacts *contacts) {
    add_bld_json(mx_entry_get_text(contacts->dialog->entry),
                 mx_entry_get_text(contacts->dialog->entry),
                 contacts->info->sock->sock);
}

