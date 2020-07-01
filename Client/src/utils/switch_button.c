#include "client.h"

GtkWidget *mx_switch_button_constuctor(char *button_name) {
    GtkWidget *button = gtk_switch_new();
    GtkStyleContext *context = gtk_widget_get_style_context(button);

    gtk_style_context_add_class(context, button_name);
    gtk_widget_set_name(button, button_name);
    gtk_widget_set_size_request(button, 4, 4);

    return button;
}

void mx_switch_button_delete(GtkWidget *button) {
    gtk_widget_destroy(button);
}
