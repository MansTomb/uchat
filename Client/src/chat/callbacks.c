#include "client.h"

void mx_send_message(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    // action "mx_send_message" esitamated return always_success
    printf("Sended\n");
    if (chat && widget) {};
}
