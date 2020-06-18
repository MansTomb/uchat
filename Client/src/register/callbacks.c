#include "client.h"

void mx_back_to_login_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;
    
    if(app && info){};
    mx_register_screen_hide(info);
    mx_login_screen_show(info);

    printf("clicked button Back on reg window\n");
}

void mx_reg_user_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;

    if(app && info){};
    // action "mx_make_register" estimated return mx_success_register
    if (mx_reg_data_validate(info->windows->reg)) {
        // mx_register_screen_hide(info);
        // mx_chat_screen_show(info);
        mx_register_build_json_wrapper(info);
    }
    printf("clicked button Register on reg window\n");
}
