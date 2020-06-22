#include "client.h"

void mx_login_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;
    t_login *log = info->windows->log;

    if (mx_login_data_validate(log)) {
        g_timer_stop(info->timer);
        pthread_join(info->thread.timer, NULL);
        mx_login_build_json_wrapper(info);
        mx_login_screen_hide(info);
        mx_main_chat_screen_show(info);
    }
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
