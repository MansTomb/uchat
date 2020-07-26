#include "client.h"

static void create_combo(t_info *info, t_cont_move *mv) {
    char *grp = NULL;
    t_list *list = info->cl_data->cont_grp_names;

    for (size_t i = 0; i < list->size; ++i) {
        grp = ((t_group *)mx_get_index(list, i)->data)->name;
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(mv->combo), grp);
    }
}

void mx_cont_move_build(t_info *info) {
    t_cont_move *cmove = malloc(sizeof(t_cont_move));

    cmove->builder = gtk_builder_new();
    gtk_builder_add_from_file(cmove->builder, MX_GLADE_CM, NULL);
    cmove->dialog = mx_gobject_builder(cmove->builder, "dialog");
    cmove->combo = mx_gobject_builder(cmove->builder, "combo");
    gtk_builder_connect_signals(cmove->builder, cmove); 
    create_combo(info, cmove);
    cmove->info = info;
    MX_GSIG_CON(cmove->dialog, "delete-event", 
                                      G_CALLBACK(mx_cont_move_destroy), cmove);
    gtk_widget_show(cmove->dialog);
}

void mx_cont_move_destroy(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_cont_move *cmove = data;

    gtk_widget_destroy(cmove->dialog);
    free(cmove);
}
