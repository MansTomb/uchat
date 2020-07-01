#include "client.h"

static void attach_signals(t_info *info, t_change_password *new) {
    MX_GSIG_CON(new->changebt, "clicked",
                     MX_CB(mx_on_click_change_pass_change), info);
    MX_GSIG_CON(new->cancelbt, "clicked",
                     MX_CB(mx_on_click_change_pass_cancel), info);
}

static void attach_layout(t_change_password *new, GtkWidget *fixed) {
    gtk_fixed_put(GTK_FIXED(fixed), new->old_pass, 20, 20);
    gtk_fixed_put(GTK_FIXED(fixed), new->new_pass, 20, 60);
    gtk_fixed_put(GTK_FIXED(fixed), new->changebt, 20, 100);
    gtk_fixed_put(GTK_FIXED(fixed), new->cancelbt, 100, 100);
}

static void show(t_info *info, t_change_password *new, GtkWidget *fixed) {
    info->windows->change_password = new;
    attach_signals(info, new);
    attach_layout(new, fixed);
    gtk_window_set_position (GTK_WINDOW(new->dialog), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(new->dialog, 240, 160);
    gtk_widget_show(new->dialog);
    gtk_widget_show(new->old_pass);
    gtk_widget_show(new->new_pass);
    gtk_widget_show(new->changebt);
    gtk_widget_show(new->cancelbt);
    gtk_widget_show(fixed);
}

void mx_change_pass_constructor(t_info *info) {
    t_change_password *new = malloc(sizeof(t_change_password));
    GtkWidget *action_area;
    GtkWidget *fixed;

    if (new && info) {
        new->dialog = gtk_dialog_new();
        new->old_pass = mx_entry_constructor("change_pass_old_pass");
        new->new_pass = mx_entry_constructor("change_pass_new_pass");
        new->changebt = mx_button_constuctor("Change", "change_changebt");
        new->cancelbt = mx_button_constuctor("Cancel", "change_cancelbt");
        action_area = gtk_dialog_get_content_area(GTK_DIALOG(new->dialog));
        fixed = mx_fixed_constructor("chage_fixed", 240, 160);
        gtk_entry_set_visibility(GTK_ENTRY(new->old_pass), FALSE);
        gtk_entry_set_visibility(GTK_ENTRY(new->new_pass), FALSE);
        gtk_entry_set_placeholder_text(GTK_ENTRY(new->old_pass), "Old Password");
        gtk_entry_set_placeholder_text(GTK_ENTRY(new->new_pass), "New Password");
        gtk_container_add(GTK_CONTAINER(action_area), fixed);
        show(info, new, fixed);
    }
}

void mx_change_pass_destructor(t_info *info) {
    t_change_password *change_password = info->windows->change_password;

    gtk_widget_destroy(change_password->old_pass);
    gtk_widget_destroy(change_password->new_pass);
    gtk_widget_destroy(change_password->changebt);
    gtk_widget_destroy(change_password->cancelbt);
    gtk_widget_destroy(change_password->dialog);
    info->windows->change_password = NULL;
}
