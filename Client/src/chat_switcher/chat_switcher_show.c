#include "client.h"

static void show_switcher(GtkWidget *widget, gpointer data) {
    if(data) {};
    gtk_widget_show(widget);
}

void mx_chat_switcher_show(t_info *info) {
    GtkCallback func = show_switcher;

    gtk_container_foreach(GTK_CONTAINER(info->windows->chat_switcher->box), func, NULL);
    gtk_widget_show(info->windows->chat_switcher->scrollable);
    gtk_widget_show(info->windows->chat_switcher->box);
    mx_show_chat(NULL, (t_chat *)mx_get_index(info->chat_list, 0)->data);
}
