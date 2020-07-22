#include "client.h"

static bool validate(t_invite_user *inv) {
    if (mx_entry_text_exist(inv->entry)) {
        if (mx_validate_chars((char *)mx_entry_get_text(inv->entry))) {
            return true;
        }
        else
            mx_dialog_warning_create(NULL, "Not valid characters in field!");
    }
    else
        mx_dialog_warning_create(NULL, MX_FIELDS_NOTEMPTY);
    return false;
}

void mx_inv_cancel(GtkWidget *widget, gpointer data) {
    t_invite_user *inv = data;

    mx_invite_user_destroy(inv);
}

void mx_inv_invite(GtkWidget *widget, gpointer data) {
    t_invite_user *inv = data;

    if (validate(inv)) {
        /* zapros */
        mx_invite_user_destroy(inv);
    }
}
