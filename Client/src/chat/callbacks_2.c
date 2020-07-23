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

    if (chat->ctype > 1)
        mx_ban_user_build(chat->info, chat);
    else {
        gtk_widget_hide(chat->banbt);
        gtk_widget_show(chat->unbanbt);

        // zaprosi
    }
}

void mx_unban_user(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    if (chat->ctype > 1)
        mx_unban_user_build(chat->info, chat);
    else {
        gtk_widget_hide(chat->unbanbt);
        gtk_widget_show(chat->banbt);

        // zaprosi
    }
}

void mx_invite_user(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    mx_invite_user_build(chat->info, chat);
}

void mx_on_scroll_edge(GtkWidget *widget, GtkPositionType pos, gpointer data) {
    t_chat *chat = data;

    printf("Load messages netop\n");
    if (GTK_POS_TOP == pos) {
        printf("Load messages\n");
        /* Load message */
    }
}

gboolean mx_chat_stack_click(GObject *gobject, GParamSpec *pspec, gpointer user_data) {
    t_info *info = user_data;
    GValue val = G_VALUE_INIT;
    GtkWidget *vchild = gtk_stack_get_visible_child(GTK_STACK(info->windows->ms->chat_stack));

    g_assert(!G_VALUE_HOLDS_BOOLEAN(&val));
    g_value_init(&val, G_TYPE_BOOLEAN);
    g_value_set_boolean(&val, FALSE);

    gtk_container_child_set_property(GTK_CONTAINER(info->windows->ms->chat_stack), vchild, "needs-attention", &val);
    return FALSE;
}
