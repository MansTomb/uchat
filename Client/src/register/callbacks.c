#include "client.h"

void back_to_login_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;
    
    if(app && info){};
    mx_register_screen_hide(info);
    mx_login_screen_show(info);

    printf("clicked button Back on reg window\n");
}

void reg_user_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;

    if(app && info){};
    mx_register_screen_hide(info);
    mx_chat_screen_show(info);
    send(info->sock->sock, "Privet", 6, 0);
    printf("clicked button Register on reg window\n");
}
