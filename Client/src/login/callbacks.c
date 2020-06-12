#include "client.h"

void mx_login_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;
    t_login *log = info->windows->log;

    if(app && info){};
    if (mx_entry_text_exist(log->username_entry) && mx_entry_text_exist(log->password_entry)) {
        // mx_login_build_json(info);
        mx_login_screen_hide(info);
        mx_main_chat_screen_show(info);
    } else
        mx_login_entry_empty(info);
    printf("clicked button Login\n");
}

void mx_register_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;
    
    mx_login_screen_hide(info);
    mx_register_screen_show(info);

    if(app && info){};

    send(info->sock->sock, "Privet", 6, 0);
    printf("clicked button Register\n");
}
