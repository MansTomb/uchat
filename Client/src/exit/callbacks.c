#include "client.h"

void mx_on_click_logout(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_exit_destructor(info);
    if (widget && data) {};
}
void mx_on_click_close(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_exit_destructor(info);
    if (widget && data) {};
}
