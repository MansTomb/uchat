#include "client.h"

static bool validate(t_unban_user *ban) {
    if (mx_entry_text_exist(ban->entry)) {
        if (mx_validate_chars((char *)mx_entry_get_text(ban->entry))) {
            return true;
        }
        else
            mx_dialog_warning_create(NULL, "Not valid characters in field!");
    }
    else
        mx_dialog_warning_create(NULL, MX_FIELDS_NOTEMPTY);
    return false;
}

void mx_unban_cancel(GtkWidget *widget, gpointer data) {
    t_unban_user *ban = data;

    mx_unban_user_destroy(ban);
}

void mx_unban_ban(GtkWidget *widget, gpointer data) {
    t_unban_user *ban = data;

    if (validate(ban)) {
        /* zapros */
        mx_unban_user_destroy(ban);
    }
}
