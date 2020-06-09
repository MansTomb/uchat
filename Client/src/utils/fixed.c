#include "client.h"

GtkWidget *mx_fixed_constructor(char *name, gint widht, gint height) {
    GtkWidget *new = gtk_fixed_new();
    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_widget_set_name(new, name);
    gtk_widget_set_size_request(new, widht, height);

    return new;
}

void mx_fixed_put(GtkWidget *fixed, GtkWidget *widget, gint x, gint y) {
    gtk_fixed_put(GTK_FIXED(fixed), widget, x, y);
}
