#include "server.h"

int mx_send_to_peer(t_info *info, t_peer *peer) {
    // size_t len_to_send;
    ssize_t send_count;
    // size_t send_total = 0;

    char newbuf[1024];

    sprintf(newbuf, "%s: %s", mx_peer_get_addres_str(peer), info->sock->buffer);
    send_count = send(peer->socket, newbuf, strlen(newbuf), 0);

    info->sock->buffer[0] = '\0';
    info->sock->valread = 0;

    if (send_count < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            printf("peer is not ready right now, try again later.\n");
        else {
            perror("send() from peer error");
            return -1;
        }
    }
    else if (send_count == 0) {
        printf("send()'ed 0 bytes. It seems that peer can't accept data right now. Try again later.\n");
    }





    // if (info) {}
    // printf("Ready for send() to %s.\n", mx_peer_get_addres_str(peer));
    // do {
    //     // If sending message has completely sent and there are messages in queue, why not send them?
    //     if (peer->current_sending_byte < 0 ||
    //         peer->current_sending_byte >= sizeof(peer->sending_buffer)) {
    //         printf("There is no pending to send() message, maybe we can find one in queue... ");
    //         if (mx_dequeue(&peer->send_buffer, &peer->sending_buffer) != 0) {
    //             peer->current_sending_byte = -1;
    //             printf("No, there is nothing to send() anymore.\n");
    //             break;
    //         }
    //         printf("Yes, pop and send() one of them.\n");
    //         peer->current_sending_byte = 0;
    //     }

    //     // Count bytes to send.
    //     len_to_send = sizeof(peer->sending_buffer) - peer->current_sending_byte;
    //     if (len_to_send > MX_MAX_SEND_SIZE)
    //         len_to_send = MX_MAX_SEND_SIZE;

    //     printf("Let's try to send() %zd bytes... ", len_to_send);
    //     send_count = send(peer->socket, (char *)&peer->sending_buffer + peer->current_sending_byte, len_to_send, 0);
    //     if (send_count < 0) {
    //         if (errno == EAGAIN || errno == EWOULDBLOCK) {
    //             printf("peer is not ready right now, try again later.\n");
    //         }
    //         else {
    //             perror("send() from peer error");
    //             return -1;
    //         }
    //     }
    //     // we have read as many as possible
    //     else if (send_count < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
    //         break;
    //     }
    //     else if (send_count == 0) {
    //         printf("send()'ed 0 bytes. It seems that peer can't accept data right now. Try again later.\n");
    //         break;
    //     }
    //     else if (send_count > 0) {
    //         peer->current_sending_byte += send_count;
    //         send_total += send_count;
    //         printf("send()'ed %zd bytes.\n", send_count);
    //     }
    // } while (send_count > 0);

    // printf("Total send()'ed %zu bytes.\n", send_total);
    return 0;
}
