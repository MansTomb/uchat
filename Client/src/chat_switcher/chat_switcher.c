#include "client.h"

static void if_chat_showed_then_hide(t_list_node *node) {
    t_chat *chat = node->data;

    if (chat->showed_chat)
        mx_chat_screen_hide(node->data);
}

void mx_hide_chat(GtkWidget *widget, gpointer data) {
    if (widget){};
    t_info *info = data;

    mx_foreach_list(info->chat_list, if_chat_showed_then_hide);
}

void mx_show_chat(GtkWidget *widget, gpointer data) {
    if (widget && data) {};

    mx_chat_screen_show(data);
}

void mx_chat_switcher_add_chat(t_info *info, t_chat *chat) {
    GtkWidget *newbt = mx_button_constuctor(chat->chat_name, "chat_chooser_button");

    MX_GSIG_CON(newbt, "clicked", MX_CB(mx_hide_chat), info);
    MX_GSIG_CON(newbt, "clicked", MX_CB(mx_show_chat), chat);
    gtk_box_pack_start(GTK_BOX(info->windows->chat_switcher->box), newbt, TRUE, FALSE, 0);
}
