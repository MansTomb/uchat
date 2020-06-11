#include "client.h"

static void hide_switcher(GtkWidget *widget, gpointer data) {
    if(data) {};
    gtk_widget_show(widget);
}

void mx_chat_switcher_hide(t_info *info) {
    GtkCallback func = hide_switcher;

    gtk_container_foreach(GTK_CONTAINER(info->windows->chat_switcher->box), func, NULL);
    gtk_widget_hide(info->windows->chat_switcher->box);
    mx_hide_chat(NULL, info);
}
