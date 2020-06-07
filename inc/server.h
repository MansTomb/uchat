#include "uchat.h"

#define MX_NO_SOCKET -1
#define MAX_MESSAGES_BUFFER_SIZE 10

typedef struct sockaddr_in t_saddr;

typedef struct  s_message {                         // t_message
    char sender[128];
    char data[512];
}               t_message;

typedef struct s_message_queue {                    // t_message_queue
    int size;
    t_message *data;
    int current;
}               t_message_queue;

typedef struct  s_peer {                            // t_peer
    int socket;
    struct sockaddr_in addres;

    // t_message_queue send_buffer;  // Messages that waiting for send.

    /* Buffered sending message.
    *
    * In case we doesn't send whole message per one call send().
    * And current_sending_byte is a pointer to the part of data
    * that will be send next call.
    */
    // t_message sending_buffer;
    size_t current_sending_byte;

    /* The same for the receiving message. */
    // t_message receiving_buffer;
    size_t current_receiving_byte;
}               t_peer;

typedef struct  s_sock {                            // t_sock
    int master_socket;
    int addrlen;
    t_saddr address;
    int opt;
    int max_sd;

    t_peer connection_list[MAX_CLIENTS];

    int client_sockets[MAX_CLIENTS];

    fd_set readfds;
    fd_set writefds;
    fd_set exceptfds;

    char buffer[1024];
    char read_stdin_buffer[1024]; // buffer for server stdin
    int valread;
}               t_sock;

typedef struct  s_info {
    t_sock *sock;
}               t_info;


/* Utils */

    /* True utils for easy init */
void mx_initialize_zero_int_arr(int *arr, int size);

    /* Peer.c */
int mx_delete_peer(t_peer *peer);
int mx_create_peer(t_peer *peer);

    /* Message_queue.c */
int mx_create_message_queue(int queue_size, t_message_queue *queue);

    /* Message.c */

/* Sockets */

    /* Create and initialazing */
void mx_socket_bind_to_port(t_sock *sock);
void mx_socket_specify_maximum_connections_to_master(int sock, int con_num);
t_sock *mx_sockets_create_struct(int port);
void mx_sockets_initialize(t_sock *sock, int port);

    /* Loop func */
void mx_sockets_loop(t_info *info);
void mx_loop_handler(t_info *info);
void mx_handle_new_connection(t_info *info);
void mx_handle_incoming_data(t_info *info);

/* Signals */

// int mx_setup_signals();


void mx_shutdown_properly(t_info *info);
