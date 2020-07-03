#include "client.h"

static void attach_signals(t_contacts *contacts, t_group_create *dialog) {
    MX_GSIG_CON(dialog->dialog_crtbt, "clicked",
                     MX_CB(mx_contact_group_create), contacts);
    MX_GSIG_CON(dialog->dialog_cancelbt, "clicked",
                     MX_CB(mx_contact_group_cancel), contacts);
}

static void attach_layout(t_group_create *new, GtkWidget *fixed) {
    mx_fixed_put(fixed, new->dialog_crtbt, 10, 110);
    mx_fixed_put(fixed, new->dialog_cancelbt, 140, 110);
    mx_fixed_put(fixed, new->entry, 20, 40);
}

t_group_create *mx_contacts_group_create_dialog_constructor(t_info *info,
                                             t_contacts *contacts) {
    t_group_create *new = malloc(sizeof(t_group_create));
    GtkWidget *action_area;

    new->dialog = gtk_dialog_new();
    new->fixed = mx_fixed_constructor("contacts_fixed", 240, 160);
    new->dialog_cancelbt = mx_button_constuctor("Cancel", "contacts_group_button_cancel");
    new->dialog_crtbt = mx_button_constuctor("Create", "contacts_group_button_add");
    new->entry = mx_entry_constructor("contact_add_dialog");

    gtk_entry_set_placeholder_text(GTK_ENTRY(new->entry), "Group Name");
    gtk_window_set_position(GTK_WINDOW(new->dialog), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(new->dialog, 240, 160);
    action_area = gtk_dialog_get_content_area(GTK_DIALOG(new->dialog));
    gtk_container_add(GTK_CONTAINER(action_area), new->fixed);

    attach_layout(new, new->fixed);
    attach_signals(contacts, new);

    gtk_widget_show_all(new->dialog);
    return new;
}

void mx_contacts_group_create_dialog_destructor(t_group_create *dialog) {
    gtk_widget_destroy(dialog->entry);
    gtk_widget_destroy(dialog->dialog_crtbt);
    gtk_widget_destroy(dialog->dialog_cancelbt);
    gtk_widget_destroy(dialog->fixed);
    gtk_widget_destroy(dialog->dialog);
    free(dialog);
}
