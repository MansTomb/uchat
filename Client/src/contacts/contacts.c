#include "client.h"

void mx_contacts_show(t_info *info) {
    t_contacts *contacts = info->windows->contacts;

    if (contacts == NULL)
        contacts = info->windows->contacts = mx_contacts_constructor(info);

    info->current_window = info->windows->contacts;
    
    gtk_widget_show(contacts->treeview);
    gtk_widget_show(contacts->crtgrp);
    gtk_widget_show(contacts->addbt);
}

void mx_contacts_hide(t_info *info) {
    t_contacts *contacts = info->windows->contacts;
    
    info->current_window = NULL;

    gtk_widget_hide(contacts->treeview);
    gtk_widget_hide(contacts->crtgrp);
    gtk_widget_hide(contacts->addbt);
}
