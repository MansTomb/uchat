#include "client.h"

static gboolean validate_empty_entry(t_login *log) {
    if ((!mx_entry_text_exist(log->username_entry) 
     && mx_entry_text_exist(log->password_entry))
     || (mx_entry_text_exist(log->username_entry) 
     && !mx_entry_text_exist(log->password_entry))) {
        // mx_login_build_json(info);
        return false;
    }
    return true;
}

static gboolean validate_password_chars(t_login *log) {
    const char *text = mx_entry_get_text(log->password_entry);
    size_t len = strlen(text);

    for (size_t i = 0; i < len; ++i) {
        if (!isprint(text[i]))
            return false;
    }
    return true;
}

gboolean mx_login_data_validate(t_login *log) {
    if (validate_empty_entry(log)) {
        if (validate_password_chars(log)) {
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
