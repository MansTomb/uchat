#include "client.h"

gboolean mx_on_key_press(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_chat *chat = data;

    if (event->key.keyval == GDK_KEY_Return
     && !(event->key.state & GDK_SHIFT_MASK)) {
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

gboolean mx_chat_stack_click(GObject *gobject, GParamSpec *pspec,
                                                         gpointer user_data) {
    t_info *info = user_data;
    GValue val = G_VALUE_INIT;
    GtkWidget *vchild = gtk_stack_get_visible_child(
                                    GTK_STACK(info->windows->ms->chat_stack));

    g_assert(!G_VALUE_HOLDS_BOOLEAN(&val));
    g_value_init(&val, G_TYPE_BOOLEAN);
    g_value_set_boolean(&val, FALSE);

    gtk_container_child_set_property(
                                GTK_CONTAINER(info->windows->ms->chat_stack),
                                vchild,
                                "needs-attention",
                                &val);
    return FALSE;
}
