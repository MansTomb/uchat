#include "client.h"

void mx_contacts_move(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_cont_move_build(info);
}

void mx_contacts_delete(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_del_cnt_json(info);
}

void mx_group_delete(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_del_group_json(info);
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
