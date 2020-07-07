#include "client.h"

void mx_register_screen_build(t_info *info, t_register *reg) {
    if (reg == NULL)
        info->windows->reg = reg = malloc(sizeof(t_register));

    reg->builder = gtk_builder_new();
    gtk_builder_add_from_file(reg->builder, "./Resources/glade/register_screen.glade", NULL);

    reg->password_entry = GTK_WIDGET(gtk_builder_get_object(reg->builder, "password_entry"));
    reg->passwordc_entry = GTK_WIDGET(gtk_builder_get_object(reg->builder, "passwordc_entry"));
    reg->username_entry = GTK_WIDGET(gtk_builder_get_object(reg->builder, "username_entry"));
    reg->window = GTK_WIDGET(gtk_builder_get_object(reg->builder, "register_window"));
    gtk_builder_connect_signals(reg->builder, info);

    gtk_widget_show(reg->window);
}

void mx_register_screen_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->reg->window);
    free(info->windows->reg);
    info->windows->reg = NULL;
}

void mx_on_click_back(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_register_screen_destroy(info);
    mx_login_screen_build(info, info->windows->log);
}

void mx_reg_user_on_click(GtkWidget *widget, gpointer user_data) {
    t_info *info = (t_info *)user_data;

    if(widget && info){};
    // action "mx_make_register" estimated return mx_success_register
    if (mx_reg_data_validate(info->windows->reg)) {
        mx_register_build_json_wrapper(info);
        mx_wait_for_json(info, failed_register, success_register);
        if (mx_get_jtype(info, success_register)) {
            
        }
        else if (mx_get_jtype(info, failed_register))
            mx_dialog_warning_create(NULL, "Username already on use!");
    }
}
