#include "client.h"

void mx_conctacts_creategrp_dialog(GtkWidget *widget, gpointer data) {
    t_contacts *contacts = data;

    contacts->dialog2 = mx_contacts_group_create_dialog_constructor(contacts->info, contacts);
}

// add contact to the list
void mx_contact_group_create(GtkWidget *widget, gpointer data) {
    t_contacts *contacts = data;

    // mx_add_contact_build_json_wrapper(contacts);
    mx_contacts_group_create_dialog_destructor(contacts->dialog2);
}
void mx_contact_group_cancel(GtkWidget *widget, gpointer data) {
    t_contacts *contacts = data;

    mx_contacts_group_create_dialog_destructor(contacts->dialog2);
}
