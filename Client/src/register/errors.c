#include "client.h"

static gboolean validate_entry(t_register *reg) {
    if (mx_entry_text_exist(reg->username_entry)
        && mx_entry_text_exist(reg->password_entry)
        && mx_entry_text_exist(reg->password2_entry))
        return true;
    return false;
}

static gboolean validate_entry_chars(GtkWidget *entry) {
    const char *text = mx_entry_get_text(entry);
    size_t len = strlen(text);

    for (size_t i = 0; i < len; ++i) {
        if (!isprint(text[i]))
            return false;
    }
    return true;
}

gboolean mx_reg_data_validate(t_register *reg) {
    if (validate_entry(reg)) {
        if (validate_entry_chars(reg->username_entry)
            && validate_entry_chars(reg->password_entry)
            && validate_entry_chars(reg->password2_entry)) {
                return true;
            }
        else {
            mx_dialog_warning_create(NULL, 
                                    "All fields chars must be printable");
            return false;
        }
    }
    else {
        mx_dialog_warning_create(NULL, "All fields must not be empty!");
        return false;
    }
}
