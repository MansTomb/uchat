#include "client.h"

GtkWidget *create_main_window(GtkApplication *app) {
    GtkWidget *window = gtk_application_window_new(app);
    GtkStyleContext *context = gtk_widget_get_style_context(window);

    gtk_style_context_add_class(context, "main_window");
    gtk_widget_set_name(window, "main_window");
    gtk_window_set_title(GTK_WINDOW (window), "uchat");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW (window), WIDTH, HEIGHT);
    return window;
}
