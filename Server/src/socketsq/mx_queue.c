#include "server.h"
/*
 * Add client to queue.
 */
// void mx_queue_add(t_all *a, t_client *cl) {
//     pthread_mutex_lock(&a->clients_mutex);
//     mx_push_front(&(a->clients), (t_client *)cl);
//     a->cli_count++;
//     a->uid++;
//     pthread_mutex_unlock(&a->clients_mutex);
// }
/*
 * Delete client from queue.
 */
// void mx_queue_del(t_all *a, int uid) {
//     t_list *q = a->clients;

//     pthread_mutex_lock(&a->clients_mutex);
//     if (q != NULL && MX_UID(q) == uid) {
//         a->clients = a->clients->next;
//         free(MX_DATA(q));
//         return;
//     }
//     while (q) {
//         if (q->next)
//             if (((t_client *)q->next->data)->uid == uid) {
//                 free((t_client *)q->next->data);
//                 q->next = q->next->next;
//                 break;
//             }
//         q = q->next;
//     }
//     a->cli_count--;
//     pthread_mutex_unlock(&a->clients_mutex);
// }

void mx_handle_disconnect(t_all *a, t_client *client) {
    //Check if it was for closing , and also read the
    //incoming message
    //Somebody disconnected , get his details and print
    // getpeername(client->socket, (struct sockaddr *)&sock->address,
    //             (socklen_t *)&sock->addrlen);
    printf("Host disconnected, ip %s:%d\n" ,
            inet_ntoa(client->addr.sin_addr), ntohs(client->addr.sin_port));

    //Close the socket and mark as MX_NO_SOCKET in list for reuse
    close(client->socket);
    client->socket = MX_NO_SOCKET;
    a->cli_count--;
    // free(client->cli_copy_for_tread);
}

void mx_dup_client(t_all *a, t_client *q, int *i) {
    pthread_mutex_lock(&a->clients_mutex);

    *i = a->current_client;
    q->addr = a->clients[*i].addr;
    q->socket = a->clients[*i].socket;
    q->uid = a->clients[*i].uid;
    sprintf(q->name, "%s", a->clients[*i].name);
    // q->cli_copy_for_tread = q;

    pthread_mutex_unlock(&a->clients_mutex);
}

char *mx_get_peer_addres_str(t_client *peer) {
    static char res[INET_ADDRSTRLEN + 10];
    // socklen_t *addrlen = NULL;

    // getpeername(peer->socket, (struct sockaddr *)&peer->addr,
    //             (socklen_t *)addrlen);
    sprintf(res, "%s:%d",
            inet_ntoa(peer->addr.sin_addr), ntohs(peer->addr.sin_port));

    return res;
}
