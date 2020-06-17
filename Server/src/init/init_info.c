#include "server.h"

t_sock *sockets_create_struct(void) {
    t_sock *new = malloc(sizeof(t_sock));

    if (new) {
        new->opt = TRUE;
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            new->connection_list[i].socket = MX_NO_SOCKET;
            new->connection_list[i].uid = -1;
            // mx_create_peer(&new->connection_list[i]);
        }
    }
    else
        printf("sock malloc error\n");
    return new;
}

t_info *mx_init_info() {
    t_info *info = malloc(sizeof(t_info));

    if (info)
        info->sock = sockets_create_struct();
    else
        printf("info malloc error\n");

    // mx_init_ssl(info->sock->ctx);

    return info;
}
