#include "server.h"

static void socket_new_accept(int *new_sock, t_sock *sock) {
    if ((*new_sock = accept(sock->master_socket,
                           (struct sockaddr *)&sock->address,
                           (socklen_t*)&sock->addrlen)) < 0)
        {
            perror("Accept new connection error!\n");
            exit(EXIT_FAILURE);
        }
}

static void socket_new_add_to_arr_of_sockets(t_sock *sock, int *new_socket) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        //if position is empty
        if (sock->client_sockets[i] == 0 ) {
            sock->client_sockets[i] = *new_socket;
            printf("Adding to list of sockets as %d\n", i);
            break;
        }
    }
}

void mx_handle_new_connection(t_info *info) {
    int new_socket;

    if (FD_ISSET(info->sock->master_socket, &info->sock->readfds)) {
        socket_new_accept(&new_socket, info->sock);

        //inform user of socket number - used in send and receive commands
        printf("New connection, socket fd is %d, ip is: %s, port: %d\n",
               new_socket, inet_ntoa(info->sock->address.sin_addr),
               ntohs(info->sock->address.sin_port));

        //send new connection greeting message
        // if( send(new_socket, message, strlen(message), 0) != (ssize_t)strlen(message) )
        // {
        //     perror("send");
        // }
        //add new socket to array of sockets
        socket_new_add_to_arr_of_sockets(info->sock, &new_socket);
    }
}
