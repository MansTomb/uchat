#include "server.h"

static void socket_new_accept(int *new_sock, t_sock *sock) {
    if ((*new_sock = accept(sock->master_socket,
                           (struct sockaddr *)&sock->address,
                           (socklen_t *)&sock->addrlen)) < 0) {
        perror("Accept new connection error!\n");
        exit(EXIT_FAILURE);
    }
    printf("New connection, socket fd is %d, ip is %s:%d\n",
           *new_sock, inet_ntoa(sock->address.sin_addr),
           ntohs(sock->address.sin_port));
}

static void socket_new_add_to_arr_of_sockets(t_sock *sock, int *new_socket) {
    int i;

    for (i = 0; i < MAX_CLIENTS; ++i) {
        if (sock->connection_list[i].socket == MX_NO_SOCKET) {
            sock->connection_list[i].socket = *new_socket;
            sock->connection_list[i].addres = sock->address;
            printf("Adding to list of sockets as %d\n", i);
            break;
        }
    }
    if (i == MAX_CLIENTS) {
        printf("no place for new connection.\n");
        close(*new_socket);
    }
}

void mx_handle_new_connection(t_info *info) {
    int new_socket;

    if (FD_ISSET(info->sock->master_socket, &info->sock->readfds)) {
        socket_new_accept(&new_socket, info->sock);
        socket_new_add_to_arr_of_sockets(info->sock, &new_socket);
    }
}
