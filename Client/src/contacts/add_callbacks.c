#include "client.h"

void mx_conctacts_add_dialog(GtkWidget *widget, gpointer data) {
    t_contacts *contacts = data;
    
    contacts->dialog = mx_contacts_add_dialog_constructor(contacts->info, contacts);
    if (widget && contacts) {};
}

void mx_contact_add(GtkWidget *widget, gpointer data) {
    t_contacts *contacts = data;

    mx_contacts_add_dialog_destructor(contacts->dialog);
    if (widget && data) {};
}
void mx_contact_add_cancel(GtkWidget *widget, gpointer data) {
    t_contacts *contacts = data;

    mx_contacts_add_dialog_destructor(contacts->dialog);
    if (widget && data) {};
}
