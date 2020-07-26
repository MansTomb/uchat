#include "client.h"

void mx_left_room(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    mx_left_chat_wrapper(chat);
}

void mx_ban_user(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;
    t_chat_member *member = NULL;

    if (chat->ctype > 1)
        mx_ban_user_build(chat->info, chat);
    else {
        member = mx_find_uid_private(chat);
        if (member)
            mx_ban_user_wrapper(chat, member->uid);
        gtk_widget_hide(chat->banbt);
        gtk_widget_show(chat->unbanbt);
    }
}

void mx_unban_user(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;
    t_chat_member *member = NULL;

    if (chat->ctype > 1)
        mx_unban_user_build(chat->info, chat);
    else {
        member = mx_find_uid_private(chat);
        if (member)
            mx_unban_user_wrapper(chat, member->uid);
        gtk_widget_hide(chat->unbanbt);
        gtk_widget_show(chat->banbt);
        
    }
}

void mx_invite_user(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    mx_invite_user_build(chat->info, chat);
}
