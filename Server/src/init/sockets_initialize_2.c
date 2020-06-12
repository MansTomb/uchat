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

void mx_init_db(t_sock *sock) {
    int rc;

    if ((rc = sqlite3_open("Server/db/uchat.db", &sock->db))) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(sock->db));
        exit(EXIT_FAILURE);
    }
    else
        printf("Opened database successfully\n");

}
