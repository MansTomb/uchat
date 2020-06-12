#include "client.h"

static void attach_layout(t_info *info, t_login *log) {
    mx_layout_put(info->layout, log->username_label, 540, 245);
    mx_layout_put(info->layout, log->username_entry, 540, 260);
    mx_layout_put(info->layout, log->password_label, 540, 295);
    mx_layout_put(info->layout, log->password_entry, 540, 310);
    mx_layout_put(info->layout, log->loginbt, 640, 360);
    mx_layout_put(info->layout, log->registerbt, 540, 360);
}

static void attach_signals(t_info *info, t_login *log) {
    MX_GSIG_CON(log->loginbt, "clicked", MX_CB(login_on_click), info);
    MX_GSIG_CON(log->registerbt, "clicked", MX_CB(register_on_click), info);
}

t_login *mx_login_constructor(t_info *info) {
    t_login *new = malloc(sizeof(t_login));

    if (new) {
        new->loginbt = mx_button_constuctor("Login", "loginbt");
        new->registerbt = mx_button_constuctor("Register", "registerbt");
        new->username_label = mx_label_constructor("username_label", "Username");
        new->username_entry = mx_entry_constructor("username_entry");
        new->password_label = mx_label_constructor("password_label", "Password");
        new->password_entry = mx_entry_constructor("password_entry");

        new->back_image = mx_background_image_constructor(info, BACKIMAGE_PATH);
        gtk_entry_set_visibility(GTK_ENTRY(new->password_entry), FALSE);
        mx_css_from_file(info, "./Resources/css/login.css");

        attach_signals(info, new);
        attach_layout(info, new);
    }
    return new;
}
