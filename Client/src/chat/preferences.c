#include "client.h"

static void set_preferences_ctype1(t_chat *chat) {
    gtk_widget_hide(chat->invbt);

    if (chat->role == -1) {
        gtk_widget_hide(chat->entry);
        gtk_widget_hide(chat->sendbt);
        gtk_widget_hide(chat->sendimgbt);
    }
    if (chat->role == 1) {
        gtk_widget_show(chat->entry);
        gtk_widget_show(chat->sendbt);
        gtk_widget_show(chat->sendimgbt);
    }
}

static void set_preferences_ctype2(t_chat *chat) {
    if (chat->role == 1) {
        gtk_widget_hide(chat->banbt);
        gtk_widget_hide(chat->unbanbt);
        gtk_widget_hide(chat->invbt);
    }
    else if (chat->role == -1) {
        gtk_widget_hide(chat->banbt);
        gtk_widget_hide(chat->unbanbt);
        gtk_widget_hide(chat->invbt);
        gtk_widget_hide(chat->entry);
        gtk_widget_hide(chat->sendbt);
        gtk_widget_hide(chat->sendimgbt);
    }
}

static void set_preferences_ctype3(t_chat *chat) {
    if (chat->role != 2) {
        gtk_widget_hide(chat->banbt);
        gtk_widget_hide(chat->unbanbt);
        gtk_widget_hide(chat->invbt);
        gtk_widget_hide(chat->entry);
        gtk_widget_hide(chat->sendbt);
        gtk_widget_hide(chat->sendimgbt);
    }
}

void mx_set_chat_preferences(t_chat *chat) {
    if (chat->cid == 1)
        gtk_widget_hide(chat->leavebt);
    if (chat->ctype == 1)
        set_preferences_ctype1(chat);
    if (chat->ctype == 2)
        set_preferences_ctype2(chat);
    if (chat->ctype == 3)
        set_preferences_ctype3(chat);
}
