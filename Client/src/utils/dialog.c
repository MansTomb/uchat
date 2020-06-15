#include "client.h"

void mx_dialog_warning_create(GtkWidget *parent, char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent), 0,
                                         GTK_MESSAGE_WARNING,
                                         GTK_BUTTONS_OK, "\n\n%s", message);

    g_signal_connect_swapped (dialog,
                            "response",
                            MX_CB (gtk_widget_destroy),
                            dialog);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(dialog, 160, 120);
    gtk_widget_show_all(dialog);
}
