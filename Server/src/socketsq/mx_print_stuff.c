#include "server.h"
/*
 * Strip CRLF.
 */
void mx_strip_newline(char *s) {
    while (*s != '\0') {
        if (*s == '\r' || *s == '\n') {
            *s = '\0';
        }
        s++;
    }
}
// /*
//  * Print list of active clients.
//  */
// void mx_print_active_clients(t_all *a, int connfd) {
//     char s[64];

//     pthread_mutex_lock(&a->clients_mutex);
//     for (t_list *q = a->clients; q; q = q->next) {
//         sprintf(s, "<< [%d] %s\r\n", MX_UID(q), MX_NAME(q));
//         mx_send_msg_self(s, connfd);
//     }
//     pthread_mutex_unlock(&a->clients_mutex);
// }
// /*
//  * Print ip address.
//  */
// void mx_print_client_addr(struct sockaddr_in addr) {
//     printf("%d.%d.%d.%d",
//            addr.sin_addr.s_addr & 0xff,
//            (addr.sin_addr.s_addr & 0xff00) >> 8,
//            (addr.sin_addr.s_addr & 0xff0000) >> 16,
//            (addr.sin_addr.s_addr & 0xff000000) >> 24);
// }
