#include "client.h"

gboolean mx_get_tactive(GtkWidget *widget) {
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
}
