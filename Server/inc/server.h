#pragma once
#include "uchat.h"
#include "macroses.h"
#include "db.h"

/* Maximum bytes that can be send() or recv() via net by one call.
 * It's a good idea to test sending one byte by one.
 */
#define MX_MAX_SEND_SIZE 1024

/* Size of send queue (messages). */
#define MX_MAX_MESSAGES_BUFFER_SIZE 10

#define MX_SENDER_MAXSIZE 128
#define MX_DATA_MAXSIZE 512

#define MX_NO_SOCKET -1
#define MX_NO_PEER -1

#define MX_DB_PATH "Server/db/uchat.db"
#define MX_SERVERLOG_PATH "Server/tmp/serverlogs"
#define MX_EMAIL_PATH "Server/tmp/sendmail"

// Macros cJSON
#define MX_TYPE(x)      (cJSON_GetObjectItem(x, "json_type")->valueint)
#define MX_SET_TYPE(x, y) (cJSON_SetNumberValue(cJSON_GetObjectItem(x, "json_type"), y))
#define MX_VINT(x, y)   (cJSON_GetObjectItem(x, y)->valueint)
#define MX_VSTR(x, y)   (cJSON_GetObjectItem(x, y)->valuestring)
// #define MX_DEL(x, y)    (cJSON_DeleteItemFromObject(x, y))


typedef struct sockaddr_in t_saddr;

typedef struct s_peer {                            // t_peer
    int socket;
    int uid;
    struct sockaddr_in addres;

    // t_message_queue send_buffer;  // Messages that waiting for send.

    /* Buffered sending message.
    *
    * In case we doesn't send whole message per one call send().
    * And current_sending_byte is a pointer to the part of data
    * that will be send next call.
    */
    // t_message sending_buffer;
    char sending_buffer[MX_MAX_SEND_SIZE];
    size_t current_sending_byte;

    /* The same for the receiving message. */
    // t_message receiving_buffer;
    char receiving_buffer[MX_MAX_SEND_SIZE];
    size_t current_receiving_byte;
}              t_peer;

typedef struct s_sock {                            // t_sock
    int master_socket;
    int addrlen;
    t_saddr address;

    int opt;
    int max_sd;

    SSL_CTX *ctx;
    SSL *ssl;

    sqlite3 *db;

    struct s_peer connection_list[MAX_CLIENTS];

    fd_set readfds;
    fd_set writefds;
    fd_set exceptfds;
}              t_sock;

typedef struct s_info {
    t_sock *sock;
}              t_info;

typedef struct s_db_cli {
    int uid[128];
    int count;
}              t_db_cli;

/* Init */

    /* daemonize.c */
void mx_daemonize(t_sock *sock);

    /* init_info.c */
t_info *mx_init_info();

    /* sockets_initialize.c sockets_initialize_2.c */
void mx_sockets_initialize(t_sock *sock, int port);

void mx_socket_bind_to_port(t_sock *sock);
void mx_socket_specify_maximum_connections_to_master(int sock, int con_num);
// void mx_init_db(t_sock *sock);

/* Sockets */

    /* Loop func */
void mx_sockets_loop(t_info *info);
void mx_handle_new_connection(t_info *info);
void mx_handle_disconnect(t_sock *sock, t_peer *client);
void mx_handle_incoming_data(t_info *info);
void mx_shutdown_properly(t_info *info, int code);

    /* Receive_message.c */
int mx_receive_from_peer(t_info *info, t_peer *peer);

    /* Send_message.c */
void mx_send_message_all(t_sock *sock, char *buff, int uid);
void mx_send_msg_self(t_sock *sock, t_peer *peer);
int mx_send_msg_client(t_sock *sock, char *buff, int uid);
void mx_send_msg_number_of_clients(t_sock *sock, char *buff, int *uid);

    /* message_handler.c */
void mx_message_handler(t_info *info, t_peer *peer);
void mx_response_db(t_info *info, t_peer *peer, int type, cJSON *get);

    /* func_response_db.c */
void mx_db_registration(t_info *info, t_peer *peer, int type, cJSON *get);
void mx_db_authorization(t_info *info, t_peer *peer, int type, cJSON *get);
void mx_db_delete(t_info *info, t_peer *peer, int type, cJSON *get);
void mx_db_change_password(t_info *info, t_peer *peer, int type, cJSON *get);
void mx_db_create_personal_chat(t_info *info, t_peer *peer, int type, cJSON *get);

void mx_db_send_message(t_info *info, t_peer *peer, int type, cJSON *get);
void mx_db_update_profile(t_info *info, t_peer *peer, int type, cJSON *get);
void mx_db_add_new_contact(t_info *info, t_peer *peer, int type, cJSON *get);
void mx_db_del_contact(t_info *info, t_peer *peer, int type, cJSON *get);

/* Utils */

    /* True utils for easy init */
void mx_initialize_zero_int_arr(int *arr, int size);
void mx_strip_newline(char *s);
void mx_json_to_sending_buffer(t_peer *peer, cJSON *json);

void mx_message_on_mail(char *email);

void mx_print_serv_out(cJSON *json, char *buff);

/* Signals */

int mx_setup_signals(void);

// void mx_init_ssl(SSL_CTX *ctx);
