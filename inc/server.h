#include "uchat.h"

typedef struct sockaddr_in t_saddr;

typedef struct s_sock {
    int master_socket;
    int addrlen;
    int max_sd;

    int client_sockets[MAX_CLIENTS];

    fd_set readfds;
    t_saddr address;
    int opt;

    int valread;
} t_sock;

typedef struct s_info {
    t_sock *sock;

} t_info;


/* Utils */

    /* True utils for easy init */
void mx_initialize_zero_int_arr(int *arr, int size);


/* Sockets */

    /* Create and initialazing */
void mx_socket_bind_to_port(t_sock *sock);
void mx_socket_specify_maximum_connections_to_master(int sock, int con_num);
t_sock *mx_sockets_create_struct(int port);
void mx_sockets_initialize(t_sock *sock, int port);

    /* Loop func */
void mx_sockets_loop(t_info *info);
void mx_handle_new_connection(t_info *info);
void mx_handle_incoming_data(t_info *info);
void mx_socketset_clear(t_sock *sock);
void mx_socket_add_master_to_set(t_sock *sock);
void mx_socket_add_child_to_set(t_sock *sock);
