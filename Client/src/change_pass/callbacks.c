#include "client.h"

void mx_on_cp_cancel(GtkWidget *widget, gpointer data) {
    t_change_password *cp = data;

    mx_change_password_destroy(NULL, NULL, cp->info);
}
void mx_on_cp_change(GtkWidget *widget, gpointer data) {
    t_change_password *cp = data;

    if (mx_cp_validate(cp)) {
            mx_chg_pass_json(cp->info,
                             mx_entry_get_text(cp->oldpass),
                             mx_entry_get_text(cp->newpass1));
            if (mx_get_jtype(cp->info, success_change_password)) {
                mx_change_password_destroy(NULL, NULL, cp->info);
            }
            else {
                mx_dialog_warning_create(NULL, "Changing password error!\n");
            }
    }
}
