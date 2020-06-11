#include "server.h"

int mx_send_check(t_sock *sock, t_peer *client, int n) {
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

int mx_recv_check(t_sock *sock, t_peer *client, int n) {
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            printf("peer is not ready right now, try again later.\n");
        else {
            perror("recv() from peer error");
            mx_handle_disconnect(sock, client);
        }
    }
    // else if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
    //     return -1;
    // }
    // If recv() returns 0, it means that peer shutdown client.
    else if (n == 0) {
        // printf("recv() 0 bytes. Peer sshutdown.\n");
        mx_handle_disconnect(sock, client);
    }
    return 0;
}
