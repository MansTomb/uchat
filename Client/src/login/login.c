#include "client.h"

static t_login *login_constructor() {
    t_login *new = malloc(sizeof(t_login));

    if (new) {
        new->loginbt = mx_button_constuctor("Login", "loginbt");
        new->registerbt = mx_button_constuctor("Register", "registerbt");
        new->username_entry = mx_entry_constructor("username_entry");
        new->password_entry = mx_entry_constructor("password_entry");
        new->username_label = mx_label_constructor("username_label", "Username");
        new->password_label = mx_label_constructor("password_label", "Password");

        gtk_entry_set_visibility(GTK_ENTRY(new->password_entry), FALSE);
    }
    return new;
}

static void attach_layout(t_info *info, t_login *log) {
    gtk_layout_put(GTK_LAYOUT(info->layout), log->username_label, WIDTH / 2 - 100, HEIGHT / 2 - 115);
    gtk_layout_put(GTK_LAYOUT(info->layout), log->username_entry, WIDTH / 2 - 100, HEIGHT / 2 - 100);
    gtk_layout_put(GTK_LAYOUT(info->layout), log->password_label, WIDTH / 2 - 100, HEIGHT / 2 - 65);
    gtk_layout_put(GTK_LAYOUT(info->layout), log->password_entry, WIDTH / 2 - 100, HEIGHT / 2 - 50);
    gtk_layout_put(GTK_LAYOUT(info->layout), log->loginbt, WIDTH / 2, HEIGHT / 2);
    gtk_layout_put(GTK_LAYOUT(info->layout), log->registerbt, WIDTH / 2 - 100, HEIGHT / 2);
    gtk_widget_show_all(info->main_window);
}

static void attach_signals(t_info *info, t_login *log) {
    g_signal_connect(log->loginbt, "clicked", G_CALLBACK(login_on_click), info);
    g_signal_connect(log->registerbt, "clicked", G_CALLBACK(register_on_click), info);
}

void mx_login_screen_create(t_info *info) {
    t_login *log = login_constructor();

    info->current_window = log;

    mx_background_image_show(info);
    mx_css_from_file(info, "./Resources/css/login.css");
    attach_signals(info, log);
    attach_layout(info, log);
}
