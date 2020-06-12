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

void mx_sockets_initialize(t_sock *sock, int port) {
    mx_init_db(sock);
    socket_master_create(&sock->master_socket);
    socket_master_allow_multiple_connections(&sock->master_socket, &sock->opt);
    socket_type_set(&sock->address, port);
    mx_socket_bind_to_port(sock);
    mx_socket_specify_maximum_connections_to_master(sock->master_socket, 128);
    sock->max_sd = sock->master_socket;
    sock->addrlen = sizeof(sock->address);
    printf("Waiting for incoming connections.\n");
}
