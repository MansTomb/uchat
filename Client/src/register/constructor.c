#include "client.h"

static void attach_layout(t_info *info, t_register *reg) {
    mx_layout_put(info->layout, reg->username_label, 540, 245);
    mx_layout_put(info->layout, reg->username_entry, 540, 260);
    mx_layout_put(info->layout, reg->password_label, 540, 295);
    mx_layout_put(info->layout, reg->password_entry, 540, 310);
    mx_layout_put(info->layout, reg->password2_label, 540, 345);
    mx_layout_put(info->layout, reg->password2_entry, 540, 360);
    mx_layout_put(info->layout, reg->backbt, 515, 410);
    mx_layout_put(info->layout, reg->registerbt, 640, 410);
}

static void attach_signals(t_info *info, t_register *reg) {
    MX_GSIG_CON(reg->backbt, "clicked", MX_CB(mx_back_to_login_on_click), info);
    MX_GSIG_CON(reg->registerbt, "clicked", MX_CB(mx_reg_user_on_click), info);
}

t_register *mx_register_constructor(t_info *info) {
    t_register *new = malloc(sizeof(t_register));

    if (new) {
        new->registerbt = mx_button_constuctor("Register", "registerbt");
        new->backbt = mx_button_constuctor("Back To Login", "backbt");
        new->username_label = mx_label_constructor("username_label", "Username");
        new->username_entry = mx_entry_constructor("username_entry");
        new->password_label = mx_label_constructor("password_label", "Password");
        new->password_entry = mx_entry_constructor("password_entry");
        new->password2_label = mx_label_constructor("password2_label", "Confirm Password");
        new->password2_entry = mx_entry_constructor("password2_entry");

        mx_css_from_file(info, "./Resources/css/register.css");
        new->back_image = mx_background_image_constructor(info, BACKIMAGE_PATH);
        gtk_entry_set_visibility(GTK_ENTRY(new->password_entry), FALSE);
        gtk_entry_set_visibility(GTK_ENTRY(new->password2_entry), FALSE);
        attach_layout(info, new);
        attach_signals(info, new);
    }
    return new;
}
