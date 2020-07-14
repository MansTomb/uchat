#include "client.h"

void mx_set_vnoti(t_main_screen *ms, char *chat_name, gboolean value) {
    GtkWidget *child = gtk_stack_get_child_by_name(GTK_STACK(ms->chat_stack), chat_name);
    GValue val = G_VALUE_INIT;

    g_assert(!G_VALUE_HOLDS_BOOLEAN(&val));
    g_value_init(&val, G_TYPE_BOOLEAN);
    g_value_set_boolean(&val, value);

    gtk_container_child_set_property(GTK_CONTAINER(ms->chat_stack), child, "needs-attention", &val);
}
