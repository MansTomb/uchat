#include "client.h"

void mx_exit_constructor(t_info *info) {
    t_exit *new = malloc(sizeof(t_exit));
    GtkWidget *action_area;

    if (new) {
        new->dialog = gtk_dialog_new();
        new->fixed = mx_fixed_constructor("exit_fixed", 160, 100);
        new->logout = mx_button_constuctor("Logout", "exit_logout");
        new->close = mx_button_constuctor("Exit Without Logout", "exit_close");

        gtk_window_set_position(GTK_WINDOW(new->dialog), GTK_WIN_POS_CENTER);
        gtk_widget_set_size_request(new->dialog, 160, 100);
        action_area = gtk_dialog_get_content_area(GTK_DIALOG(new->dialog));
        gtk_container_add(GTK_CONTAINER(action_area), new->fixed);

        mx_fixed_put(new->fixed, new->logout, 20, 80);
        mx_fixed_put(new->fixed, new->close, 100, 80);

        MX_GSIG_CON(new->logout, "clicked", G_CALLBACK(mx_on_click_logout), info);
        MX_GSIG_CON(new->close, "clicked", G_CALLBACK(mx_on_click_close), info);
        gtk_widget_show_all(new->dialog);
        info->windows->exit = new;
    }
}

void mx_exit_destructor(t_info *info) {
    t_exit *exit = info->windows->exit;

    gtk_widget_destroy(exit->logout);
    gtk_widget_destroy(exit->close);
    gtk_widget_destroy(exit->fixed);
    gtk_widget_destroy(exit->dialog);
    info->windows->exit = NULL;
}
