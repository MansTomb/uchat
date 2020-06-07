#include "client.h"

GtkWidget *mx_frame_constructor(char *name, char *label, gint w, gint h) {
    GtkWidget *new = gtk_frame_new(label);
    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_widget_set_name(new, name);
    gtk_widget_set_size_request(new, w, h);

    return new;
}
