#include "server.h"
/*
 * Send message to all clients but the sender,
 * if uid == -1 - send_message_all
 */
void mx_send_message_all(t_all *a, char *s, int uid) {
    pthread_mutex_lock(&a->clients_mutex);
    for (t_list *q = a->clients; q; q = q->next) {
        if (MX_UID(q) != uid || uid == 0) {
            if (write(MX_CONNFD(q), s, mx_strlen(s)) < 0) { //mx_send_msg
                perror(MX_ERR_CL_WR);
                break;
            }
        }
    }
    pthread_mutex_unlock(&a->clients_mutex);
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
