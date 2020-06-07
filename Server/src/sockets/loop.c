#include "server.h"

static void build_fd_sets(t_sock *sock) {
    int i;
    int sd;

    FD_ZERO(&sock->readfds);
    FD_SET(STDIN_FILENO, &sock->readfds);
    FD_SET(sock->master_socket, &sock->readfds);
    sock->max_sd = sock->master_socket;
    for (i = 0; i < MAX_CLIENTS; i++) {
        sd = sock->connection_list[i].socket;
        if (sd > MX_NO_SOCKET)
            FD_SET(sd, &sock->readfds);
        if (sd > sock->max_sd)
            sock->max_sd = sd;
    }

    FD_ZERO(&sock->writefds);
    for (i = 0; i < MAX_CLIENTS; i++)
        // if (sock->connection_list[i].socket > MX_NO_SOCKET
        //     && sock->connection_list[i].send_buffer.current > 0)
        //     FD_SET(sock->connection_list[i].socket, &sock->writefds);
        if (sock->connection_list[i].socket > MX_NO_SOCKET)
            FD_SET(sock->connection_list[i].socket, &sock->writefds);

    FD_ZERO(&sock->exceptfds);
    FD_SET(STDIN_FILENO, &sock->exceptfds);
    FD_SET(sock->master_socket, &sock->exceptfds);
    for (i = 0; i < MAX_CLIENTS; i++)
        if (sock->connection_list[i].socket > MX_NO_SOCKET)
            FD_SET(sock->connection_list[i].socket, &sock->exceptfds);
}


void mx_sockets_loop(t_info *info) {
    int activity;

    while (TRUE) {
        build_fd_sets(info->sock);
        activity = select(info->sock->max_sd + 1, &info->sock->readfds,
                          &info->sock->writefds, &info->sock->exceptfds, NULL);
        // activity = select(info->sock->max_sd + 1, &info->sock->readfds,
        //        NULL, NULL, NULL);

        mx_loop_handler(info);

        // mx_shutdown_properly(info);

//     switch (activity) {
//       case -1:
//         perror("select()");
//         shutdown_properly(EXIT_FAILURE);

//       case 0:
//         // you should never get here
//         printf("select() returns 0.\n");
//         shutdown_properly(EXIT_FAILURE);

//       default:
//         /* All set fds should be checked. */
//         if (FD_ISSET(STDIN_FILENO, &read_fds)) {
//           if (handle_read_from_stdin() != 0)
//             shutdown_properly(EXIT_FAILURE);
//         }

//         if (FD_ISSET(listen_sock, &read_fds)) {
//           handle_new_connection();
//         }

//         if (FD_ISSET(STDIN_FILENO, &except_fds)) {
//           printf("except_fds for stdin.\n");
//           shutdown_properly(EXIT_FAILURE);
//         }

//         if (FD_ISSET(listen_sock, &except_fds)) {
//           printf("Exception listen socket fd.\n");
//           shutdown_properly(EXIT_FAILURE);
//         }

//         for (i = 0; i < MAX_CLIENTS; ++i) {
//           if (connection_list[i].socket != NO_SOCKET && FD_ISSET(connection_list[i].socket, &read_fds)) {
//             if (receive_from_peer(&connection_list[i], &handle_received_message) != 0) {
//               close_client_connection(&connection_list[i]);
//               continue;
//             }
//           }

//           if (connection_list[i].socket != NO_SOCKET && FD_ISSET(connection_list[i].socket, &write_fds)) {
//             if (send_to_peer(&connection_list[i]) != 0) {
//               close_client_connection(&connection_list[i]);
//               continue;
//             }
//           }

//           if (connection_list[i].socket != NO_SOCKET && FD_ISSET(connection_list[i].socket, &except_fds)) {
//             printf("Exception client fd.\n");
//             close_client_connection(&connection_list[i]);
//             continue;
//           }
//         }
//     }

//     printf("And we are still waiting for clients' or stdin activity. You can type something to send:\n");
//   }

    }
}
