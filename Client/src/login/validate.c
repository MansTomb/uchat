#include "client.h"

static gboolean validate_empty_entry(t_login *log) {
    if (mx_entry_text_exist(log->username_entry) 
        && mx_entry_text_exist(log->password_entry)) {
        // mx_login_build_json(info);
        return true;
    }
    return false;
}

gboolean mx_login_data_validate(t_login *log) {
    char *pass = (char *)mx_entry_get_text(log->password_entry);
    char *uname = (char *)mx_entry_get_text(log->username_entry);

    if (validate_empty_entry(log)) {
        if (mx_validate_chars(pass) && mx_validate_chars(uname)) {
            return true;
        }
        else {
            mx_dialog_warning_create(NULL, 
                                    "Password must contain printable chars!");
            return false;
        }
    }
    else {
        mx_dialog_warning_create(NULL, "Fields cant be empty!");
        return false;
    }
}
