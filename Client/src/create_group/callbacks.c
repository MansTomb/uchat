#include "client.h"

void mx_on_crt_group_cancel(GtkWidget *widget, gpointer data) {
    t_group_create *gc = data;

    mx_create_group_destroy(gc->info);
}

void mx_on_crt_group_create(GtkWidget *widget, gpointer data) {
    t_group_create *gc = data;

    if (mx_entry_text_exist(gc->entry)) {
        /* 
            Do request to create with -> mx_get_text_entry(gc->entry);
            Then use mx_push_back to grp_names_list
        */
       mx_create_group_destroy(gc->info);
    }
    else
        mx_dialog_warning_create(NULL, "Group name cant be empty!");
}
