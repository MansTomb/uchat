#include "client.h"

GtkWidget *mx_label_constructor(char *name, char *text) {
    GtkWidget *new = gtk_label_new(text);
    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_widget_set_name(new, name);

    return new;
}
