#include "server.h"

static int send_check(t_all *a, int i, int n) {
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            printf("Peer is not ready right now, try again later.\n");
        else {
            perror("send() to peer error");
            mx_handle_disconnect(a, &a->clients[i]);
        }
    }
    else if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
        return -1;
    else if (n == 0) {
        printf("Peer can't accept data right now, try again later.\n");
        return -1;
    }
    return 0;
}

/*
 * Send message to all clients but the sender,
 * if uid == -1 - send_message_all
 */
void mx_send_msg_all(t_all *a, char *buff, int uid) {
    pthread_mutex_lock(&a->clients_mutex);

    // for (t_list *q = a->clients; q; q = q->next) {
    //     if (MX_UID(q) != uid || uid == 0) {
    //         if (write(MX_CONNFD(q), s, mx_strlen(s)) < 0) { //mx_send_msg
    //             perror(MX_ERR_CL_WR);
    //             break;
    //         }
    //     }
    // }
    int n;

    for (int i = 0; i < MX_MAX_CLIENTS; ++i) {
        if (a->clients[i].socket != MX_NO_SOCKET) {
            if (a->clients[i].uid != uid || uid == 0) {
                n = send(a->clients[i].socket, buff, strlen(buff), 0);
                // n = write(a->clients[i].socket, buff, strlen(buff));
                if (send_check(a, i, n) == -1)
                    break;
            }
        }
    }
    pthread_mutex_unlock(&a->clients_mutex);
}
// /*
//  * Send message to client
//  */
// void mx_send_msg_client(t_all *a, char *s, int uid) {
//     pthread_mutex_lock(&a->clients_mutex);
//     for (t_list *q = a->clients; q; q = q->next) {
//         if (MX_UID(q) == uid) {
//             if (write(MX_CONNFD(q), s, mx_strlen(s)) < 0) { //mx_send_msg
//                 perror(MX_ERR_CL_WR);
//                 break;
//             }
//         }
//     }
//     pthread_mutex_unlock(&a->clients_mutex);
// }
/*
 * Send message to sender
 */
void mx_send_msg_self(const char *s, int connfd) {
    if (send(connfd, s, strlen(s), 0) < 0) {
        perror("Client loop: write error");
        // exit(EXIT_FAILURE);
    }
}
