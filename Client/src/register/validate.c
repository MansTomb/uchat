#include "client.h"

static gboolean validate_entry(t_register *reg) {
    if (mx_entry_text_exist(reg->username_entry)
        && mx_entry_text_exist(reg->password_entry)
        && mx_entry_text_exist(reg->passwordc_entry))
        return true;
    mx_dialog_warning_create(NULL, "All fields must not be empty!");
    return false;
}

static gboolean password_match(t_register *reg) {
    const char *text1 = mx_entry_get_text(reg->password_entry);
    const char *text2 = mx_entry_get_text(reg->passwordc_entry);

    if (!strcmp(text1, text2))
        return true;
    mx_dialog_warning_create(NULL, "Password must match!");
    return false;
}

static gboolean validate_entryes(t_register *reg) {
    if (mx_validate_chars((char *)mx_entry_get_text(reg->username_entry))
        && mx_validate_chars((char *)mx_entry_get_text(reg->password_entry))
        && mx_validate_chars((char *)mx_entry_get_text(reg->passwordc_entry)))
        return true;
    mx_dialog_warning_create(NULL, "Wrong characters in fields!");
    return false;
}

gboolean mx_reg_data_validate(t_register *reg) {
    if (validate_entry(reg))
        if (validate_entryes(reg))
            if (password_match(reg))
                return true;
    return false;
}
