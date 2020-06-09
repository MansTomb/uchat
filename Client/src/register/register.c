#include "client.h"

void mx_register_screen_show(t_info *info) {
    t_register *reg = info->windows->reg;

    if (!reg)
        reg = info->windows->reg = mx_register_constructor(info);

    mx_background_image_show(reg->back_image);
    gtk_widget_show(reg->backbt);
    gtk_widget_show(reg->registerbt);
    gtk_widget_show(reg->username_label);
    gtk_widget_show(reg->username_entry);
    gtk_widget_show(reg->password_label);
    gtk_widget_show(reg->password_entry);
    gtk_widget_show(reg->password2_label);
    gtk_widget_show(reg->password2_entry);
}

void mx_register_screen_hide(t_info *info) {
    t_register *reg = info->windows->reg;

    gtk_widget_hide(reg->backbt);
    gtk_widget_hide(reg->registerbt);
    gtk_widget_hide(reg->username_label);
    gtk_widget_hide(reg->username_entry);
    gtk_widget_hide(reg->password_label);
    gtk_widget_hide(reg->password_entry);
    gtk_widget_hide(reg->password2_label);
    gtk_widget_hide(reg->password2_entry);
    mx_background_image_hide(reg->back_image);
}
