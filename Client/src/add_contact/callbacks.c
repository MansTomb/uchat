#include "client.h"

void mx_on_add_contact_cancel(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;

    mx_add_contact_destroy(ac->info);
}

// make_search_user
void mx_on_add_contact_add(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;
    char *grpname = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ac->combobox));

    if (mx_entry_text_exist(ac->entry) && grpname) {
        mx_add_cnt_json_wrapper(ac);
        mx_create_table(ac->info, ac->info->windows->cont);
        mx_add_contact_destroy(ac->info);
    }
    else
        mx_dialog_warning_create(NULL, "Contact username or group cant be empty!");
}
