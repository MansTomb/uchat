#include "client.h"

static bool validate(t_ban_user *ban, char *name) {
    if (mx_entry_text_exist(ban->entry)) {
        if (mx_validate_chars((char *)mx_entry_get_text(ban->entry))) {
            if (mx_find_cmember(ban->chat, name))
                return true;
            else
                mx_dialog_warning_create(NULL, "User not exist!");
        }
        else
            mx_dialog_warning_create(NULL, MX_NONPRINT);
    }
    else
        mx_dialog_warning_create(NULL, MX_FIELDS_NOTEMPTY);
    return false;
}

void mx_ban_cancel(GtkWidget *widget, gpointer data) {
    t_ban_user *ban = data;

    mx_ban_user_destroy(NULL, NULL, ban);
}

void mx_ban_ban(GtkWidget *widget, gpointer data) {
    t_ban_user *ban = data;
    char *name = (char *)mx_entry_get_text(ban->entry);

    if (validate(ban, name)) {
        mx_ban_user_wrapper(ban->chat, mx_find_cmember(ban->chat, name)->uid);
        mx_ban_user_destroy(NULL, NULL, ban);
    }
}
