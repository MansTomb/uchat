#include "uchat.h"

GtkWidget *mx_layout_constructor(char *name, int width, int height) {
    GtkWidget *new = gtk_layout_new(NULL, NULL);

    gtk_widget_set_name(new, name);
    gtk_widget_set_size_request(new, width, height);
    return new;
}
