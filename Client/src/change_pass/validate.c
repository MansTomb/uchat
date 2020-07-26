#include "client.h"

static gboolean check_isprint(const char *text) {
    for (size_t i = 0; i < strlen(text); ++i) {
        if (!isprint(text[i]))
            return false;
    }
    return true;
}

gboolean mx_cp_validate(t_change_password *cp) {
    if (mx_entry_text_exist(cp->oldpass) &&
        mx_entry_text_exist(cp->newpass1) &&
        mx_entry_text_exist(cp->newpass2)) {
            if (strcmp(mx_entry_get_text(cp->newpass1),
                       mx_entry_get_text(cp->newpass2)) == 0) {
                if (mx_validate_chars(mx_entry_get_text(cp->oldpass))
                 && mx_validate_chars(mx_entry_get_text(cp->newpass1))
                 && mx_validate_chars(mx_entry_get_text(cp->newpass2)))
                    return true;
                else
                    mx_dialog_warning_create(NULL, MX_PASS_NONPRINT);
            }
            else
                mx_dialog_warning_create(NULL, MX_NEWPASS_NOTEQUAL);
        }
    else
        mx_dialog_warning_create(NULL, MX_FIELDS_NOTEMPTY);
    return false;
}
