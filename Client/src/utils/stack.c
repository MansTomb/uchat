#include "client.h"

GtkWidget *mx_stack_constructor(char *name) {
    GtkWidget *new = gtk_stack_new();
    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_widget_set_name(new, name);

    return new;
}

void mx_stack_add(GtkWidget *stack, GtkWidget *child, char *name, char *title) {
    gtk_stack_add_titled(GTK_STACK(stack), child, name, title);
}
