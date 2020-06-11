#include "server.h"

void mx_socket_bind_to_port(t_sock *sock) {
    if (bind(sock->master_socket, (struct sockaddr *)&sock->address,
             sizeof(sock->address)) < 0) {
        perror("Socket binding to port FAIL\n");
        exit(EXIT_FAILURE);
    }
}

void mx_socket_specify_maximum_connections_to_master(int sock, int con_num) {
    if (listen(sock, con_num) < 0) {
        perror("Listening failed\n");
        exit(EXIT_FAILURE);
    }
}

void mx_set_nonblock_for_stdin(void) {
    int flag;

    flag = fcntl(STDIN_FILENO, F_GETFL, 0);
    flag |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flag);
}
