#include "server.h"

int main(int argc, char *argv[]) {
    t_info *info;
    int portnumber;

    if (argc != 2)
        return(fprintf(stderr, "Usage: %s <port>\n", argv[0]) * 0 + 1);
    portnumber = atoi(argv[1]);
    if (portnumber <= 0 || portnumber >= 65535)
        return(fprintf(stderr, "error: <port> can't be > 65534\n") * 0 + 1);

    if (mx_setup_signals() != 0)
        exit(EXIT_FAILURE);

    info = mx_init_info();
    mx_daemonize();
    mx_sockets_initialize(info->sock, atoi(argv[1]));
    mx_sockets_loop(info);
    mx_shutdown_properly(info, 0);

    return 0;
}
