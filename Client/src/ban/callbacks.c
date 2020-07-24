#include "client.h"

static bool validate(t_ban_user *ban) {
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

void mx_ban_cancel(GtkWidget *widget, gpointer data) {
    t_ban_user *ban = data;

    mx_ban_user_destroy(ban);
}

void mx_ban_ban(GtkWidget *widget, gpointer data) {
    t_ban_user *ban = data;
    char *name = (char *)mx_entry_get_text(ban->entry);

    mx_ban_user_wrapper(ban->chat, mx_find_cmember(ban->chat, name)->uid);
    mx_ban_user_destroy(ban);
}