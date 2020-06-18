#include "client.h"

gboolean mx_toggle_get_active(GtkWidget *widget) {
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
}
