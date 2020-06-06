#include "server.h"



void mx_socketset_clear(t_sock *sock) {
    int i;

    FD_ZERO(&sock->readfds);
    FD_ZERO(&sock->writefds);
    FD_ZERO(&sock->errorfds);

    FD_ZERO(&sock->readfds);
    FD_SET(STDIN_FILENO, &sock->readfds);
    FD_SET(sock->master_socket, &sock->readfds);
    for (i = 0; i < MAX_CLIENTS; i++)
        if (connection_list[i].socket != NO_SOCKET)
            FD_SET(connection_list[i].socket, read_fds);

    FD_ZERO(write_fds);
    for (i = 0; i < MAX_CLIENTS; ++i)
        if (connection_list[i].socket != NO_SOCKET && connection_list[i].send_buffer.current > 0)
            FD_SET(connection_list[i].socket, write_fds);

    FD_ZERO(except_fds);
    FD_SET(STDIN_FILENO, except_fds);
    FD_SET(listen_sock, except_fds);
    for (i = 0; i < MAX_CLIENTS; ++i)
        if (connection_list[i].socket != NO_SOCKET)
            FD_SET(connection_list[i].socket, except_fds);
}

void mx_socket_add_master_to_set(t_sock *sock) {
    FD_SET(sock->master_socket, &sock->readfds);
    sock->max_sd = sock->master_socket;
}

void mx_socket_add_child_to_set(t_sock *sock) {
    int sd;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        //socket descriptor
        sd = sock->client_sockets[i];

        //if valid socket descriptor then add to read list
        if (sd > 0)
            FD_SET(sd, &sock->readfds);

        //highest file descriptor number, need it for the select function
        if (sd > sock->max_sd)
            sock->max_sd = sd;
    }
}
