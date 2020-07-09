#include "client.h"

void mx_on_add_contact_cancel(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;

    mx_add_contact_destroy(ac->info);
}
void mx_on_add_contact_add(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;

printf("mx_on_add_contact_add\n");
    // mx_add_contact_build_json_wrappre
    // get text from entry -> gtk_entry_get_text(GTK_ENTRY(ac->entry));
    // get group name -> gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ac->combobox));
    mx_add_contact_destroy(ac->info);
}
