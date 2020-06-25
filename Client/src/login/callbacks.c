#include "client.h"

void mx_login_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;
    t_login *log = info->windows->log;

    if (mx_login_data_validate(log)) {
        mx_login_build_json_wrapper(info);
        mx_wait_for_json(info, success_authorization, failed_authorization);
        if (mx_get_jtype(info, success_authorization)) {
            g_timer_stop(info->timer);
            pthread_join(info->thread.timer, NULL);
            mx_save_login_data(info);
            mx_get_json_contact(info);
            mx_login_screen_hide(info);
            mx_main_chat_screen_show(info);
        }
        else if (mx_get_jtype(info, failed_authorization))
            mx_dialog_warning_create(NULL, "Invalid login or password!");
    }
}

void mx_register_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;
    
    mx_login_screen_hide(info);
    mx_register_screen_show(info);
}
