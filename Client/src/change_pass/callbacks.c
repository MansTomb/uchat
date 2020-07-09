#include "client.h"

void mx_on_cp_cancel(GtkWidget *widget, gpointer data) {
    t_change_password *cp = data;

    mx_change_password_destroy(cp->info);
}
void mx_on_cp_change(GtkWidget *widget, gpointer data) {
    t_change_password *cp = data;

    if (mx_cp_validate(cp)) {
        /* SEND;
            old pass -> mx_entry_get_text(cp->oldpass)
            new pass1 -> mx_entry_get_text(cp->newpass1)
            new pass2 -> mx_entry_get_text(cp->newpass2)

            if success: close window
            if nonsucces: say that old password wrong
        */
    }
    // mx_change_password_destroy(cp->info);
}
