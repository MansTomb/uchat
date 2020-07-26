#include "client.h"

static int validate(t_delete_profile *dp) {
    GtkWidget *p1 = dp->pass1;
    GtkWidget *p2 = dp->pass2;

    if (mx_entry_text_exist(p1) && mx_entry_text_exist(p2)) {
        if (!strcmp(mx_entry_get_text(p1), mx_entry_get_text(p2))) {
            return true;
        }
        else
            mx_dialog_warning_create(NULL, "Password not equal!");
    }
    else
        mx_dialog_warning_create(NULL, MX_FIELDS_NOTEMPTY);
    return false;
}

void mx_del_profile_cancel(GtkWidget *widget, gpointer data) {
    t_delete_profile *dp = data;

    mx_delete_profile_destroy(NULL, NULL, dp->info);
}
void mx_del_profile_delete(GtkWidget *widget, gpointer data) {
    t_delete_profile *dp = data;

    if (validate(dp)) {
        mx_delete_user_wrapper(dp->info);
    }
}
