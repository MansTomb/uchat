#include "client.h"

gboolean mx_destroy(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_info *info = data;
    
    if (info->wchange == 0) {
        gtk_main_quit();
        return FALSE;
    }
    return TRUE;
}
