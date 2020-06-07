#include "client.h"

GtkWidget *mx_layout_constructor(char *name, int width, int height) {
    GtkWidget *new = gtk_layout_new(NULL, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(new);

    gtk_style_context_add_class(context, name);
    gtk_widget_set_name(new, name);
    gtk_layout_set_size(GTK_LAYOUT(new), width, height);
    return new;
}

void mx_layout_put(GtkWidget *layout, GtkWidget *obj, guint width, guint height) {
    guint _height;
    guint _width;

    gtk_layout_get_size(GTK_LAYOUT(layout), &_width, &_height);
    
    if (height > _height) {
        gtk_layout_set_size(GTK_LAYOUT(layout), _width, _height + (height - _height) + 50);
    }
    gtk_layout_put(GTK_LAYOUT(layout), obj, width, height);
}
