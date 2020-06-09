#include "client.h"

static void attach_layout(t_info *info, t_register *reg) {
    mx_layout_put(info->layout, reg->username_label, R_USRLB_W, R_USRLB_H);
    mx_layout_put(info->layout, reg->username_entry, R_USRENT_W, R_USRENT_H);
    mx_layout_put(info->layout, reg->password_label, R_PASLB_W, R_PASLB_H);
    mx_layout_put(info->layout, reg->password_entry, R_PASENT_W, R_PASENT_H);
    mx_layout_put(info->layout, reg->password2_label, R_PAS2LB_W, R_PAS2LB_H);
    mx_layout_put(info->layout, reg->password2_entry, R_PAS2ENT_W, R_PAS2ENT_H);
    mx_layout_put(info->layout, reg->backbt, R_BACKBT_W, R_BACKBT_H);
    mx_layout_put(info->layout, reg->registerbt, R_REGBT_W, R_REGBT_H);
}

static void attach_signals(t_info *info, t_register *reg) {
    g_signal_connect(reg->backbt, "clicked", G_CALLBACK(back_to_login_on_click), info);
    g_signal_connect(reg->registerbt, "clicked", G_CALLBACK(reg_user_on_click), info);
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
