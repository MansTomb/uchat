#include "server.h"

static void socket_master_create(int *master_socket) {
    *master_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (!master_socket) {
        perror("Master socket was not created!\n");
        exit(EXIT_FAILURE);
    }
}

static void socket_master_allow_multiple_connections(int *socket, int *opt) {
    if(setsockopt(*socket, SOL_SOCKET, SO_REUSEADDR, (char *)opt,
                 sizeof(*opt)) < 0 ) {
        perror("Master socket fail at allowing multiple connections!\n");
        exit(EXIT_FAILURE);
    }
}

static void socket_type_set(t_saddr *sock, int port) {
    sock->sin_family = AF_INET;
    sock->sin_addr.s_addr = INADDR_ANY;
    sock->sin_port = htons(port);
}

t_sock *mx_sockets_create_struct(int port) {
    t_sock *new = malloc(sizeof(t_sock));

    if (port) {};
    if (new) {
        new->opt = TRUE;
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            new->connection_list[i].socket = MX_NO_SOCKET;
            mx_create_peer(&new->connection_list[i]);
        }
        new->valread = 0;
    }
    return new;
}

void mx_sockets_initialize(t_sock *sock, int port) {
    socket_master_create(&sock->master_socket);
    socket_master_allow_multiple_connections(&sock->master_socket, &sock->opt);
    socket_type_set(&sock->address, port);
    mx_socket_bind_to_port(sock);
    mx_socket_specify_maximum_connections_to_master(sock->master_socket, 128);
    mx_set_nonblock_for_stdin();
    sock->max_sd = sock->master_socket;
    sock->addrlen = sizeof(sock->address);
    printf("Waiting for incoming connections.\n");
}
