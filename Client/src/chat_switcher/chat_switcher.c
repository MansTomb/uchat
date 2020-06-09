#include "client.h"

static void kostil(t_list_node *node) {
    t_chat *chat = node->data;

    if (chat->showed_chat)
        mx_chat_screen_hide(node->data);
}

static void hide_chat(GtkWidget *widget, gpointer data) {
    if (widget){};
    t_info *info = data;

    mx_foreach_list(info->chat_list, kostil);
}

static void show_chat(GtkWidget *widget, gpointer data) {
    if (widget && data) {};

    mx_chat_screen_show(data);
}

void mx_chat_switcher_add_chat(t_info *info, t_chat *chat, char *chat_name) {
    GtkWidget *newbt = mx_button_constuctor(chat_name, "chat_chooser_button");

    g_signal_connect(newbt, "clicked", G_CALLBACK(hide_chat), info);
    g_signal_connect(newbt, "clicked", G_CALLBACK(show_chat), chat);
    gtk_box_pack_start(GTK_BOX(info->windows->chat_switcher->box), newbt, TRUE, FALSE, 1);
    gtk_widget_show(newbt);
}
