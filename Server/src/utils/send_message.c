#include "server.h"
/*
 * Send message to all clients but the sender,
 * if uid == -1 - send_message_all
 */
void mx_send_message_all(t_sock *sock, char *buff, int uid) {
    int sd = 0;
    int n;

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        sd = sock->connection_list[i].socket;
        if (sd != MX_NO_SOCKET) {
            if (sock->connection_list[i].uid != uid || uid == 0) {
                if ((n = send(sd, buff, strlen(buff), 0)) <= 0) {
                    mx_send_check(sock, &sock->connection_list[i], n);
                }
            }
        }
    }
}
/*
 * Send message to client
 */
void mx_send_msg_client(t_sock *sock, char *buff, int uid) {
    int sd = 0;
    int n;

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        sd = sock->connection_list[i].socket;
        if (sd != MX_NO_SOCKET) {
            if (sock->connection_list[i].uid == uid) {
                if ((n = send(sd, buff, strlen(buff), 0)) <= 0) {
                    mx_send_check(sock, &sock->connection_list[i], n);
                }
            }
        }
    }
}
/*
 * Send message to sender
 */
void mx_send_msg_self(t_sock *sock, t_peer *peer, const char *buff) {
    int n = 0;

    if ((n = send(peer->socket, buff, strlen(buff), 0)) <= 0)
        mx_send_check(sock, peer, n);

}
