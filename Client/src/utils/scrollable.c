#include "client.h"

GtkWidget *mx_scrollable_constructor(char *name, GtkAdjustment *hadj,
                                                 GtkAdjustment *vadj) {
    GtkWidget *new = gtk_scrolled_window_new(hadj, vadj);

    gtk_widget_set_name(new, name);

    return new;
}
