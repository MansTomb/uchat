#include "client.h"

void mx_on_click_back(GtkWidget *widget, gpointer data) {
    if(widget && data) {};
    t_info *info = data;
printf("privet\n");
    mx_find_and_hide_screen(info);
    mx_chat_switcher_show(info);
}
