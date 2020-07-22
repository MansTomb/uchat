#include "client.h"

gboolean mx_on_key_press(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_chat *chat = data;

    if (event->key.keyval == GDK_KEY_Return && !(event->key.state & GDK_SHIFT_MASK)) {
        mx_send_message(widget, data);
        return TRUE;
    }
    return FALSE;
}
void mx_choose_dialog(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    gtk_widget_show(chat->img_dialog);
}

void mx_on_dialog_cancel(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    gtk_widget_hide(chat->img_dialog);
}

void mx_left_room(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;
}

void mx_ban_user(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    mx_ban_user_build(chat->info);
}

void mx_invite_user(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    mx_invite_user_build(chat->info);
}

void mx_on_scroll_edge(GtkWidget *widget, GtkPositionType pos, gpointer data) {
    t_chat *chat = data;

    printf("Load messages netop\n");
    if (GTK_POS_TOP == pos) {
        printf("Load messages\n");
        /* Load message */
    }
}
