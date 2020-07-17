#include "client.h"


void mx_del_profile_cancel(GtkWidget *widget, gpointer data) {
    t_delete_profile *dp = data;

    mx_delete_profile_destroy(dp->info);
}
void mx_del_profile_delete(GtkWidget *widget, gpointer data) {
    t_delete_profile *dp = data;

    if (mx_entry_text_exist(dp->pass1) && mx_entry_text_exist(dp->pass2)) {
            
        mx_delete_profile_destroy(dp->info);
    }
    else
        mx_dialog_warning_create(NULL, MX_FIELDS_NOTEMPTY);
}
