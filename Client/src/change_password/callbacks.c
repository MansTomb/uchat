#include "client.h"

void mx_on_click_change_pass_change(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_change_password *change_pass = info->windows->change_password;

    if (mx_entry_text_exist(change_pass->old_pass) && 
        mx_entry_text_exist(change_pass->new_pass)) {
        printf("sended");
        // send request to change password
    }
    else
        mx_dialog_warning_create(NULL, "Fields cant be empty!");

}
void mx_on_click_change_pass_cancel(GtkWidget *widget, gpointer data) {
    t_info *info = data;
    t_change_password *change_pass = info->windows->change_password;

    mx_change_pass_destructor(info);
}

