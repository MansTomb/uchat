#include "server.h"

static int send_check(t_sock *sock, t_peer *client, int n) {
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("Peer is not ready right now, try again later.\n");
        }
        else {
            perror("Send() from peer error");
            mx_handle_disconnect(sock, client);
        }
    }
    // we have read as many as possible
    // else if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
    //     return -1;
    // }
    else if (n == 0) {
        printf("Peer can't accept data right now, try again later.\n");
        // return -1;
    }
    return 0;
}

/*
 * Send message to all clients but the sender,
 * if uid == -1 - send_message_all
 */
void mx_send_message_all(t_sock *sock, t_peer *peer, cJSON *bd, int uid) {
    int sd = 0;
    int n;

    if (uid < 0) {
        printf("bad uid, cant send message");
        return;
    }
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        sd = sock->connection_list[i].socket;
        if (sd != MX_NO_SOCKET) {
            if (sock->connection_list[i].uid != uid || uid == 0) {
                mx_send_message_handler(sock, peer, bd, sd);
            }
        }
    }
}
/*
 * Send message to client
 */
int mx_send_msg_client(t_sock *sock, t_peer *peer, cJSON *bd, int uid) {
    int sd = 0;
    int i;

    for (i = 0; i < MAX_CLIENTS; ++i) {
        sd = sock->connection_list[i].socket;
        if (sd != MX_NO_SOCKET && sock->connection_list[i].uid == uid) {
            mx_send_message_handler(sock, peer, bd, sd);
            return 0;
        }
    }
    if (i == MAX_CLIENTS)
        return -1;
    return 0;
}

void mx_send_msg_clients(t_sock *sock, t_peer *peer, cJSON *bd, int *uid) {
    int len = 0;
    int i;

    for (i = 0; uid[i] != -1; ++i)
        len++;
    for (i = 0; i < len; ++i)
        mx_send_msg_client(sock, peer, bd, uid[i]);
}
