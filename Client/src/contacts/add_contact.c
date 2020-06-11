#include "client.h"

static void attach_signals(t_contacts *contacts, t_contact_add *dialog) {
    g_signal_connect(dialog->dialog_addbt, "clicked",
                     G_CALLBACK(mx_contact_add), contacts);
    g_signal_connect(dialog->dialog_cancelbt, "clicked",
                     G_CALLBACK(mx_contact_add_cancel), contacts);
}

static void attach_layout(t_contact_add *new, GtkWidget *fixed) {
    mx_fixed_put(fixed, new->combobox, 200, 40);
    mx_fixed_put(fixed, new->dialog_addbt, 10, 110);
    mx_fixed_put(fixed, new->dialog_cancelbt, 140, 110);
    mx_fixed_put(fixed, new->entry, 20, 40);
}

t_contact_add *mx_contacts_add_dialog_constructor(t_info *info,
                                             t_contacts *contacts) {
    t_contact_add *new = malloc(sizeof(t_contact_add));
    GtkWidget *action_area;

    new->dialog = gtk_dialog_new();
    new->combobox = gtk_combo_box_new();
    new->fixed = mx_fixed_constructor("contacts_fixed", 240, 160);
    new->dialog_cancelbt = mx_button_constuctor("Cancel", "contacts_button_cancel");
    new->dialog_addbt = mx_button_constuctor("Add", "contacts_button_add");
    new->entry = mx_entry_constructor("contact_add_dialog");

    gtk_entry_set_placeholder_text(GTK_ENTRY(new->entry), "username and group");
    gtk_window_set_position(GTK_WINDOW(new->dialog), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(new->dialog, 240, 160);
    action_area = gtk_dialog_get_content_area(GTK_DIALOG(new->dialog));
    gtk_container_add(GTK_CONTAINER(action_area), new->fixed);

    attach_layout(new, new->fixed);
    attach_signals(contacts, new);

    gtk_widget_show_all(new->dialog);
    return new;
    if(info && contacts) {};
}

void mx_contacts_add_dialog_destructor(t_contact_add *dialog) {
    gtk_widget_destroy(dialog->entry);
    gtk_widget_destroy(dialog->dialog_addbt);
    gtk_widget_destroy(dialog->dialog_cancelbt);
    gtk_widget_destroy(dialog->combobox);
    gtk_widget_destroy(dialog->fixed);
    gtk_widget_destroy(dialog->dialog);
}
