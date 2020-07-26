#include "client.h"

static void create_combo(t_info *info, t_cont_move *mv) {
    char *grp = NULL;

    for (size_t i = 0; i < info->cl_data->cont_grp_names->size; ++i) {
        grp = mx_get_index(info->cl_data->cont_grp_names, i)->data;
        gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(mv->combo), 0, grp);
    }
}

void mx_cont_move_build(t_info *info) {
    t_cont_move *cmove = malloc(sizeof(t_cont_move));

    cmove->builder = gtk_builder_new();
    gtk_builder_add_from_file(cmove->builder, "./Resources/glade/contant_move.glade", NULL);
    cmove->dialog = mx_gobject_builder(cmove->builder, "dialog");
    cmove->combo = mx_gobject_builder(cmove->builder, "combo");
    gtk_builder_connect_signals(cmove->builder, cmove);

    cmove->info = info;

    gtk_widget_show(cmove->dialog);
}

void mx_cont_move_destroy(t_cont_move *cmove) {
    gtk_widget_destroy(cmove->dialog);
    free(cmove);
}
