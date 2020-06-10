#include "server.h"

static void check_max_reached(t_all *a) {
    if ((a->cli_count + 1) == MX_MAX_CLIENTS) {
        printf("<< max clients reached\n");
        printf("<< reject ");
        // mx_print_client_addr(cli_addr);
        printf("\n");
        // close(connfd);
    }
}

static void socket_new_accept(int *new_sock, t_all *sock) {
    if ((*new_sock = accept(sock->listenfd,
                           (struct sockaddr *)&sock->address,
                           (socklen_t *)&sock->addrlen)) < 0) {
        mx_perror_and_exit("Accept new connection error!\n");
    }
    printf("New connection, socket fd is %d, ip is %s:%d\n",
           *new_sock, inet_ntoa(sock->address.sin_addr),
           ntohs(sock->address.sin_port));
}

static void socket_new_add_to_arr_of_sockets(t_all *sock, int *new_socket) {
    t_client *sd;

    pthread_mutex_lock(&sock->clients_mutex);
    for (int i = 0; i < MX_MAX_CLIENTS; ++i) {
        sd = &sock->clients[i];
        if (sd->socket == MX_NO_SOCKET) {
            sd->socket = *new_socket;
            memcpy(&sd->addr, &sock->address, sizeof(struct sockaddr));
            sock->cli_count++;
            sock->uid++;
            sock->current_client = i;
            sprintf(sd->name, "%s", mx_get_peer_addres_str(sd));
            printf("Adding to list of sockets as %d\n", i);
            break;
        }
    }
    pthread_mutex_unlock(&sock->clients_mutex);
}

void mx_accept_clients(t_all *a) {
    int new_socket;
    pthread_t tid;

    while (TRUE) {
        // if (FD_ISSET(STDIN_FILENO, &info->sock->readfds)) {
        //     if (mx_handle_read_from_stdin(info) != 0)
        //         mx_shutdown_properly(info, EXIT_FAILURE);
        //     }

        socket_new_accept(&new_socket, a);
        check_max_reached(a); // + new_s

        //send new connection greeting message
        // if( send(new_socket, message, strlen(message), 0) != (ssize_t)strlen(message) )
        //     perror("send");

        socket_new_add_to_arr_of_sockets(a, &new_socket);
        pthread_create(&tid, NULL, &handle_client, (void *)a);

        sleep(1);
    }
}
