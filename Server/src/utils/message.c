#include "server.h"

int mx_prepare_message(char *sender, char *data, t_message *message) {
    sprintf(message->sender, "%s", sender);
    sprintf(message->data, "%s", data);
    return 0;
}

int mx_print_message(t_message *message) {
    printf("Message: \"%s: %s\"\n", message->sender, message->data);
    return 0;
}

void mx_message_to_str(t_message *message, char *buff) {
    sprintf(buff, "%s: %s", message->sender, message->data);
}

int mx_handle_received_message(t_info *info, t_message *new_message) {
    mx_print_message(new_message);
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (info->sock->connection_list[i].socket != MX_NO_SOCKET) {
            if (mx_peer_add_to_send(&info->sock->connection_list[i], new_message) != 0) {
                printf("Send buffer was overflowed, we lost this message!\n");
                continue;
            }
        // printf("New message to send was enqueued right now.\n");
        }
    }
    return 0;
}
