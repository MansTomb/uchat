#include "client.h"

GtkWidget *mx_stack_switcher_constructor(char *name, GtkWidget *stack) {
    GtkWidget *new = gtk_stack_switcher_new();
    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(new), GTK_STACK(stack));

    return new;
}
