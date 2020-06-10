#include "uchat.h"

#define MX_MAX_CLIENTS 128
#define MX_BUFF_SIZE 1024
#define MX_NO_SOCKET -1

#define MX_ERR_SE_US    "usage: ./uchat_server <network port>\n"
// #define MX_ERR_SE_BI    "server: socket binding failed"
// #define MX_ERR_SE_LI    "server: socket listening failed"
#define MX_ERR_SE_AC    "server: socket accepting failed"

// #define MX_ERR_SE_MA    "server: init: malloc error"

#define MX_ERR_CL_US    "usage: ./uchat <server IP> <network port>\n"
// #define MX_ERR_CL_WR    "client loop: write error"
#define MX_ERR_CL_RE    "client loop: read error"
#define MX_ERR_CL_SO    "client: socket creation error\n"
#define MX_ERR_CL_PT    "client: inet_pton error occured\n"
#define MX_ERR_CL_CF    "client: connection failed\n"

/*
 * Macroses for lists.
 */
#define MX_A_HEAD(a)    (a->clients)
#define MX_A_DATA(a)    ((t_client *)a->clients->data)
#define MX_DATA(q)      ((t_client *)q->data)
#define MX_NAME(q)      (((t_client *)q->data)->name)
#define MX_CONNFD(q)    (((t_client *)q->data)->connfd)
#define MX_UID(q)       (((t_client *)q->data)->uid)

/*
 * Client structure.
 */
typedef struct  s_client {
    struct sockaddr_in addr; /* Client remote address */
    int socket;              /* Connection file descriptor */
    int uid;                 /* Client unique identifier */
    char name[32];           /* Client name */
    pthread_t thread;
    struct s_client *cli_copy_for_tread;
}               t_client;

typedef struct  s_all {
    int listenfd;
    int addrlen;
    struct sockaddr_in address;

    t_client clients[MX_MAX_CLIENTS];

    int current_client;
    int cli_count;
    char topic[32];
    pthread_mutex_t clients_mutex;
    // unsigned int cli_count;
    int uid;

    char buffer[1024];
    char read_stdin_buffer[1024]; // buffer for server stdin
    int valread;

}               t_all;

// static _Atomic unsigned int cli_count = 0;
// static int uid = 10;
// pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t topic_mutex = PTHREAD_MUTEX_INITIALIZER;
// static char topic[MX_BUFF_SIZE/2];

/*
 * Server.
 */

    /* init.c */
t_all *mx_init_all(void);
void mx_sockets_initialize(t_all *a, int port);

    /* init_2.c */
void mx_set_nonblock_for_stdin(void);
char *mx_init_buff_set_zero(int buffsize);
void mx_perror_and_exit(char *s);

    /*  */
void mx_daemonize(void);
void mx_accept_clients(t_all *a);
void *handle_client(void *arg);


    /* queue.c */
void mx_handle_disconnect(t_all *a, t_client *client);
void mx_dup_client(t_all *a, t_client *cli, int *i);
char *mx_get_peer_addres_str(t_client *peer);


    /* send_msg.c*/
void mx_send_msg_all(t_all *a, char *s, int uid);
// void mx_send_msg_client(t_all *a, char *s, int uid);
void mx_send_msg_self(const char *s, int connfd);



void mx_special_opt(t_all *a, t_client *cli,
                           char *buff_in, char *buff_out);

void mx_queue_del(t_all *a, int uid);

void mx_strip_newline(char *s);
void mx_print_active_clients(t_all *a, int connfd);
// void mx_print_client_addr(struct sockaddr_in addr);
