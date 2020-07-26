#include "client.h"

static bool user_exist(t_invite_user *inv) {
    t_chat_member *member = NULL;
    char *username = (char *)mx_entry_get_text(inv->entry);

    for (size_t i = 0; i < inv->chat->users->size; ++i) {
        member = mx_get_index(inv->chat->users, i)->data;
        if (strcmp(username, member->login) == 0)
            return true;
    }
    return false;
}

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

    mx_invite_user_destroy(NULL, NULL, inv);
}

void mx_inv_invite(GtkWidget *widget, gpointer data) {
    t_invite_user *inv = data;

    if (validate(inv)) {
        mx_invite_json_wrapper(inv);
        mx_invite_user_destroy(NULL, NULL, inv);
    }
}
