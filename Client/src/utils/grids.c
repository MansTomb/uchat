#include "client.h"

GtkWidget *mx_grid_constructor(char *name, int width, int height) {
    GtkWidget *new = gtk_grid_new();

    gtk_widget_set_name(new, name);
    gtk_widget_set_size_request(new, width, height);
    return new;
}
