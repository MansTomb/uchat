#include "uchat.h"

GtkWidget *mx_label_constructor(char *name, char *text) {
    GtkWidget *new = gtk_label_new(text);

    gtk_widget_set_name(new, name);

    return new;
}
