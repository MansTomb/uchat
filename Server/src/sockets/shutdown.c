#include "server.h"

void mx_shutdown_properly(t_info *info, int code) {

    close(info->sock->master_socket);
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (info->sock->connection_list[i].socket != MX_NO_SOCKET)
             close(info->sock->connection_list[i].socket);
    // mx_close_db(info->sock);

    // mx_destroy_ssl(info->sock->ctx);
    printf("Shutdown server properly.\n");
    exit(code);
}
