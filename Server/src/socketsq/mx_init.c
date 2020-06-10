#include "server.h"
/*
 * Init structure that consist of list of clients, mutexes, etc.
 */
t_all *mx_init_all(void) {
    t_all *a = malloc(sizeof(t_all));

    if (!a)
        mx_perror_and_exit("Server: init: malloc error");
    for (int i = 0; i < MX_MAX_CLIENTS; ++i) {
        a->clients[i].socket = MX_NO_SOCKET;
        bzero(a->clients[i].name, 32);
        // a->clients[i].cli_copy_for_tread = NULL;
    }
    a->valread = 0;
    a->current_client = -1;
    a->cli_count = 0;
    bzero(a->topic, 32);
    if (pthread_mutex_init(&a->clients_mutex, NULL) != 0) {
        free(a);
        mx_perror_and_exit("Server: mutex init error");
    }
    a->uid = 10;

    return a;
}
/*
 * Socket settings.
 */
static void socket_type_set(struct sockaddr_in *sock, int port) {
    sock->sin_family = AF_INET;
    sock->sin_addr.s_addr = INADDR_ANY;
    sock->sin_port = htons(port);
}
/*
 * Server bind and listen.
 */
static void bind_and_listen(t_all *a) {

    if (bind(a->listenfd, (struct sockaddr *)&a->address,
             sizeof(a->address)) < 0)
        mx_perror_and_exit("Server: socket binding failed");

    if (listen(a->listenfd, SOMAXCONN) < 0)
        mx_perror_and_exit("Server: socket listening failed");
}
// create and socket_master_allow_multiple_connections
static void socket_master_create(int *master_socket, int *sock, int *opt) {
    *master_socket = socket(AF_INET, SOCK_STREAM, 0);
    int opt = TRUE;

    if (!master_socket || master_socket == -1)
        mx_perror_and_exit("Master socket was not created!\n");

    if (setsockopt(*sock, SOL_SOCKET, SO_REUSEADDR, (char *)opt,
                 sizeof(*opt)) < 0 )
        mx_perror_and_exit("Master socket fail at allowing \
                            multiple connections!\n");
}

void mx_sockets_initialize(t_all *a, int port) {

    socket_master_create(&a->listenfd, &a->listenfd, &a->opt);
    socket_type_set(&a->address, port);
    bind_and_listen(a);
    mx_set_nonblock_for_stdin();
    a->addrlen = sizeof(a->address);
    printf("Waiting for incoming connections.\n");
}
