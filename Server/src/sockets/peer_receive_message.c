#include "server.h"

int recv_check(int n) {
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            printf("peer is not ready right now, try again later.\n");
        else {
            perror("recv() from peer error");
            return -2;
        }
    }
    else if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        return -1;
    }
    // If recv() returns 0, it means that peer shutdown client.
    else if (n == 0)
        return -2;
    return 0;
}

int mx_receive_from_peer(t_info *info, t_peer *peer) {
    size_t len_to_receive;
    size_t received_total = 0;
    size_t received_count;

     // Is completely received?
    // if (peer->current_receiving_byte >= sizeof(peer->receiving_buffer)) {
    //     printf("%s", peer->receiving_buffer);
    //     mx_send_message_all(info->sock, peer->receiving_buffer, peer->uid);

    //     // message_handler(info, &peer->receiving_buffer);
    //     peer->current_receiving_byte = 0;
    // }
    // Count bytes to send.
    len_to_receive = sizeof(peer->receiving_buffer);
    if (len_to_receive > MX_MAX_SEND_SIZE)
        len_to_receive = MX_MAX_SEND_SIZE;

    // printf("Let's try to recv() %zd bytes... ", len_to_receive);
    received_count = recv(peer->socket, (char *)&peer->receiving_buffer,
                          len_to_receive, MSG_DONTWAIT);
    if (received_count <= 0) {
        if (recv_check(received_count) == -2)
            return -1;
    }
    else if (received_count > 0) {
        peer->current_receiving_byte += received_count;
        received_total += received_count;
        // printf("recv() %zd bytes\n", received_count);
    }
    if (peer->current_receiving_byte >= sizeof(peer->receiving_buffer)) {
        printf("%s", peer->receiving_buffer);
        mx_strip_newline(peer->receiving_buffer);
        mx_send_message_all(info->sock, peer->receiving_buffer, peer->uid);

        // message_handler(info, &peer->receiving_buffer);
        peer->current_receiving_byte = 0;
    }

    // while (received_count > 0) {
    //      // Is completely received?
    //     if (peer->current_receiving_byte >= sizeof(peer->receiving_buffer)) {
    //         printf("%s", peer->receiving_buffer);
    //         mx_send_message_all(info->sock, peer->receiving_buffer, peer->uid);

    //         // message_handler(info, &peer->receiving_buffer);
    //         peer->current_receiving_byte = 0;
    //         break;
    //     }
    //     // Count bytes to send.
    //     len_to_receive = sizeof(peer->receiving_buffer) - peer->current_receiving_byte;
    //     if (len_to_receive > MX_MAX_SEND_SIZE)
    //         len_to_receive = MX_MAX_SEND_SIZE;

    //     // printf("Let's try to recv() %zd bytes... ", len_to_receive);
    //     received_count = recv(peer->socket, (char *)&peer->receiving_buffer
    //         + peer->current_receiving_byte, len_to_receive, MSG_DONTWAIT);
    //     if (received_count <= 0) {
    //         if (recv_check(received_count) == -1)
    //             break;
    //         else if (recv_check(received_count) == -2)
    //             return -1;
    //     }
    //     else if (received_count > 0) {
    //         peer->current_receiving_byte += received_count;
    //         received_total += received_count;
    //         // printf("recv() %zd bytes\n", received_count);
    //     }
    // }
    // printf("Total recv()'ed %zu bytes.\n", received_total);


    // t_message *message = malloc(sizeof(t_message));

    //     if ((info->sock->valread = read(peer->socket, info->sock->buffer, 1024)) <= 0)
    //         recv_check(info->sock, peer, info->sock->valread);
    //     else {
    //             // handle_data();
    //         // info->sock->buffer[info->sock->valread - 1] = '\0';
    //         mx_strip_newline(info->sock->buffer);
    //         // sprintf(newbuf, "%s: %s", mx_peer_get_addres_str(peer), info->sock->buffer);

    //         mx_prepare_message(mx_peer_get_addres_str(peer), info->sock->buffer, message);

    //         mx_message_to_str(message, info->sock->buffer);
    //         mx_send_message_all(info->sock, message->data, peer->uid);

    //         // message_handler(info, message);
    //         // printf("%s", info->sock->buffer);
    //     }
    return 0;
}
