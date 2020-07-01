#include "client.h"

GtkWidget *mx_scale_horizotal_constructor(char *name, gdouble min, gdouble max, gdouble step) {
    GtkWidget *new = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, min, max, step);
    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_widget_set_name(new, name);

    return new;
}

GtkWidget *mx_scale_vertical_constructor(char *name, gdouble min, gdouble max, gdouble step) {
    GtkWidget *new = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, min, max, step);
    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_widget_set_name(new, name);

    return new;
}
