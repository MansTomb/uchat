#include "client.h"

static bool validate(t_cont_move *move, char *name) {
    if (name)
        return true;
    else
        mx_dialog_warning_create(NULL, "Group not choosen!");
    return false;
}

void mx_cont_move_cancel(GtkWidget *widget, gpointer data) {
    t_cont_move *move = data;

    mx_cont_move_destroy(move);
}

void mx_cont_move_move(GtkWidget *widget, gpointer data) {
    t_cont_move *move = data;
    char *grp = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(move->combo));

    if (validate(move, grp)) {
        mx_change_contact_group(move->info, grp);
        mx_cont_move_destroy(move);
    }
}
