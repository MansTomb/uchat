#include "client.h"

GtkWidget *mx_scrollable_constructor(char *name, gint width, gint height) {
    GtkWidget *new = gtk_scrolled_window_new(NULL, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_widget_set_size_request(new, width, height);
    gtk_widget_set_name(new, name);

    return new;
}

void mx_scrollable_container_add(GtkWidget *scroll, GtkWidget *child) {
    gtk_container_add(GTK_CONTAINER(scroll), child);
}
