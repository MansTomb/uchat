#include "server.h"

void mx_sockets_loop(t_info *info) {
    while (TRUE) {
        mx_socketset_clear(info->sock);
        mx_socket_add_master_to_set(info->sock);
        mx_socket_add_child_to_set(info->sock);
        select(info->sock->max_sd + 1, &info->sock->readfds, NULL, NULL, NULL);
        mx_handle_new_connection(info);
        mx_handle_incoming_data(info);
        sleep(1);
    }
}
