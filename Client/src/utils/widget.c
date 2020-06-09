#include "client.h"

void mx_widget_destroy(GtkWidget *widget) {
    gtk_widget_hide(widget);
    gtk_widget_destroy(widget);
}
