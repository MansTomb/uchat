#include "client.h"

void mx_on_crt_group_cancel(GtkWidget *widget, gpointer data) {
    t_group_create *gc = data;

    mx_create_group_destroy(NULL, NULL, gc->info);
}

void mx_on_crt_group_create(GtkWidget *widget, gpointer data) {
    t_group_create *gc = data;

    if (mx_entry_text_exist(gc->entry)) {
        mx_send_json_group(gc->info, mx_entry_get_text(gc->entry));
        mx_create_group_destroy(NULL, NULL, gc->info);
    }
    else
        mx_dialog_warning_create(NULL, "Group name cant be empty!");
}
