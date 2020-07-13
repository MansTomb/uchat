#include "client.h"

void mx_on_add_contact_cancel(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;

    mx_add_contact_destroy(ac->info);
}

// make_search_user
void mx_on_add_contact_add(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;

    mx_add_cnt_json_wrapper(ac);
    mx_add_contact_destroy(ac->info);
}
