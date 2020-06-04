#include "uchat.h"

GtkWidget *mx_entry_constructor(char *name) {
    GtkWidget *new = gtk_entry_new();

    gtk_widget_set_name(new, name);
    gtk_entry_set_max_length(GTK_ENTRY(new), 16);
    
    return new;
}
