#include "client.h"

void mx_on_add_contact_cancel(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;

    mx_add_contact_destroy(ac->info);
}

void mx_on_add_contact_add(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;

    if (mx_entry_text_exist(ac->entry)) {
        mx_add_cnt_json_wrapper(ac);
        mx_create_table(ac->info, ac->info->windows->cont);
        mx_add_contact_destroy(ac->info);
    }
    else
        mx_dialog_warning_create(NULL, "Contact username cant be empty!");
}
