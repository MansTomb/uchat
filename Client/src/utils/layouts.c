#include "client.h"

GtkWidget *mx_layout_constructor(char *name, int width, int height) {
    GtkWidget *new = gtk_layout_new(NULL, NULL);

    gtk_widget_set_name(new, name);
    gtk_layout_set_size(GTK_LAYOUT(new), width, height);
    return new;
}

void mx_layout_put(GtkWidget *layout, GtkWidget *obj, int width, int height) {
    gtk_layout_put(GTK_LAYOUT(layout), obj, width, height);
}
