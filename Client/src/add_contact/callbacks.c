#include "client.h"

static void clear_data(t_list_node *node) {
    free(node->data);
}

void mx_clr_tmp_usr_lst(t_list *list) {
    system("leaks -q uchat");
    mx_foreach_list(list, clear_data);
    mx_delete_list(list);

    // if (list) {
    //     t_list_node *head = list->head;
    //     t_list_node *next = list->tail;

    //     while (head) {
    //         next = head->next;
    //         // MX_STRDEL(((t_user *)head->data)->login);
    //         free(head->data);
    //         free(head);
    //         head = next;
    //     }
    //     head = NULL;
    //     list->tail = NULL;
    //     list->size = 0;
    // }
}

void mx_on_add_contact_cancel(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;

    mx_clr_tmp_usr_lst(ac->info->cl_data->tmp_users);
    mx_add_contact_destroy(ac->info);
}

void mx_on_add_contact_add(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;
    char *grpname = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ac->combobox));

    if (mx_entry_text_exist(ac->entry) && grpname) {
        mx_add_cnt_json_wrapper(ac);
        mx_create_table(ac->info, ac->info->windows->cont);
        mx_clr_tmp_usr_lst(ac->info->cl_data->tmp_users);
        mx_add_contact_destroy(ac->info);
    }
    else
        mx_dialog_warning_create(NULL, "Contact username or group cant be empty!");
    mx_strdel(&grpname);
}
