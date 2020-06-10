#include "server.h"
/*
 * Send message to all clients but the sender,
 * if uid == -1 - send_message_all
 */
void mx_send_message_all(t_info *info, char *buff, int uid) {
    int sd = 0;
    // t_peer *peer = NULL;

    if (uid) {}

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        sd = info->sock->connection_list[i].socket;
        // peer = &info->sock->connection_list[i];
        if (sd != MX_NO_SOCKET) {
            // if (info->sock->connection_list[i].uid != uid || uid == 0) {
                if (send(sd, buff, strlen(buff), 0) < 0) {
                    perror("Write to descriptor failed");
                    break;
                }
            // }
        }
    }
}

/*
 * Send message to client
 */
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
// void mx_send_msg_self(const char *s, int connfd) {
//     if (write(connfd, s, mx_strlen(s)) < 0) {
//         perror(MX_ERR_CL_WR);
//         // exit(EXIT_FAILURE);
//     }
// }
