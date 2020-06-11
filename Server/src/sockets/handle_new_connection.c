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
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (sock->connection_list[i].socket == MX_NO_SOCKET) {
            sock->connection_list[i].socket = *new_socket;
            sock->connection_list[i].uid = sock->curr_uid;
            sock->connection_list[i].addres = sock->address;

            sock->connection_list[i].current_sending_byte   = -1;
            sock->connection_list[i].current_receiving_byte = 0;
            printf("Adding to list of sockets as %d\n", i);
            break;
        }
    }
    sock->curr_uid++;
}

void mx_handle_new_connection(t_info *info) {
    int new_socket;

    if (FD_ISSET(info->sock->master_socket, &info->sock->readfds)) {
        socket_new_accept(&new_socket, info->sock);

        printf("sock id = ");

        //send new connection greeting message
        // if( send(new_socket, message, strlen(message), 0) != (ssize_t)strlen(message) )
        // {
        //     perror("send");
        // }
        //add new socket to array of sockets
        socket_new_add_to_arr_of_sockets(info->sock, &new_socket);
    }
}
