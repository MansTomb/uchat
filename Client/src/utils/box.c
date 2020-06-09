#include "client.h"

GtkWidget *mx_box_constructor(char *name, gint widht, gint height, GtkOrientation orientaion) {
    GtkWidget *new = gtk_box_new(orientaion, 1);
    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_widget_set_name(new, name);
    gtk_widget_set_size_request(new, widht, height);

    return new;
}
