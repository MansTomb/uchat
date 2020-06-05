#include "client.h"

void login_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;
    
    if(app && info){};

    printf("clicked button Login\n");
}

void register_on_click(GtkApplication *app, gpointer user_data) {
    t_info *info = (t_info *)user_data;
    
    if(app && info){};

    printf("clicked button Register\n");
}
