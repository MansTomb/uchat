#include "client.h"

GtkWidget *mx_gobject_builder(GtkBuilder *builder, char *name) {
    return GTK_WIDGET(gtk_builder_get_object(builder, name));
}
