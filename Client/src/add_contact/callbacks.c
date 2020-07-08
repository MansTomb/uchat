#include "client.h"

void mx_on_add_contact_cancel(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;

    mx_add_contact_destroy(ac->info);
}
void mx_on_add_contact_add(GtkWidget *widget, gpointer data) {
    t_contact_add *ac = data;

    // mx_add_contact_build_json_wrappre
    mx_add_contact_destroy(ac->info);
}
