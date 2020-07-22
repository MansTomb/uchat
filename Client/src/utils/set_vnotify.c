#include "client.h"

void mx_set_vnoti(t_info *info, t_main_screen *ms, int cid, gboolean value) {
    if (info->cl_data->profile->vs_noty == 0)
        return;

    char name[64];
    GValue val = G_VALUE_INIT;
    GtkWidget *vchild = NULL;
    GtkWidget *child = NULL;

    sprintf(name, "%d", cid);
    vchild = gtk_stack_get_visible_child(GTK_STACK(ms->chat_stack));
    child = gtk_stack_get_child_by_name(GTK_STACK(ms->chat_stack), name);

    g_assert(!G_VALUE_HOLDS_BOOLEAN(&val));
    g_value_init(&val, G_TYPE_BOOLEAN);
    g_value_set_boolean(&val, value);

    if (child != vchild || (child == vchild && value == 0))
        gtk_container_child_set_property(GTK_CONTAINER(ms->chat_stack), child, "needs-attention", &val);
}
