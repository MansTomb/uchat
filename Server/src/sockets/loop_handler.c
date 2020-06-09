#include "server.h"

static void handle_exceptfd_list(t_info *info) {

     if (FD_ISSET(STDIN_FILENO, &info->sock->exceptfds)) {
        printf("except_fds for stdin.\n");
        mx_shutdown_properly(info, EXIT_FAILURE);
    }
    if (FD_ISSET(info->sock->master_socket, &info->sock->exceptfds)) {
        printf("Exception listen socket fd.\n");
        mx_shutdown_properly(info, EXIT_FAILURE);
    }
}

void mx_loop_handler(t_info *info) {

    if (FD_ISSET(STDIN_FILENO, &info->sock->readfds)) {
        if (mx_handle_read_from_stdin(info) != 0)
            mx_shutdown_properly(info, EXIT_FAILURE);
        }

    mx_handle_new_connection(info);
    handle_exceptfd_list(info);
    mx_handle_incoming_data(info);
}
