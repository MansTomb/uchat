#include "client.h"

GtkWidget *mx_listbox_constructor(char *name) {
    GtkWidget *new = gtk_list_box_new();

    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_widget_set_name(new, name);

    return new;
}
