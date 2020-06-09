#include "server.h"

int mx_receive_from_peer(t_info *info, t_peer *peer,
                         int (*message_handler)(t_info *, t_message *)) {
    // size_t len_to_receive;
    // ssize_t received_count;  // = 1
    // size_t received_total = 0;

    t_message *message = malloc(sizeof(t_message));
    // mx_prepare_message("s", "hello", message);
    // message_handler(info, message);

    if ((info->sock->valread = read(peer->socket, info->sock->buffer, 1024)) == 0)
        mx_handle_disconnect(info->sock, peer);
    else if (info->sock->valread < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            printf("peer is not ready right now, try again later.\n");
        else {
            perror("recv() from peer error");
            return -1;
        }
    }
    else {
            // handle_data();
        info->sock->buffer[info->sock->valread] = '\0';
        mx_strip_newline(info->sock->buffer);
        mx_prepare_message(mx_peer_get_addres_str(peer), info->sock->buffer, message);
        message_handler(info, message);
        // printf("%s", info->sock->buffer);
        send(peer->socket, info->sock->buffer, strlen(info->sock->buffer), 0);
    }

    // printf("Ready for recv() from %s.\n", mx_peer_get_addres_str(peer));
    // do {
    //     // Is completely received?
    //     if (peer->current_receiving_byte >= sizeof(peer->receiving_buffer)) {
    //         message_handler(info, &peer->receiving_buffer);
    //         peer->current_receiving_byte = 0;
    //     }

    //     // Count bytes to send.
    //     len_to_receive = sizeof(peer->receiving_buffer) - peer->current_receiving_byte;
    //     if (len_to_receive > MX_MAX_SEND_SIZE)
    //         len_to_receive = MX_MAX_SEND_SIZE;

    //     printf("Let's try to recv() %zd bytes... ", len_to_receive);
    //     received_count = recv(peer->socket, (char *)&peer->receiving_buffer + peer->current_receiving_byte, len_to_receive, MSG_DONTWAIT);
    //     if (received_count < 0) {
    //         if (errno == EAGAIN || errno == EWOULDBLOCK)
    //             printf("peer is not ready right now, try again later.\n");
    //         else {
    //             perror("recv() from peer error");
    //             return -1;
    //         }
    //     }
    //     else if (received_count < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
    //         break;
    //     }
    //     // If recv() returns 0, it means that peer gracefully shutdown. Shutdown client.
    //     else if (received_count == 0) {
    //         printf("recv() 0 bytes. Peer gracefully shutdown.\n");
    //         return -1;
    //     }
    //     else if (received_count > 0) {
    //         peer->current_receiving_byte += received_count;
    //         received_total += received_count;
    //         printf("recv() %zd bytes\n", received_count);
    //     }
    // } while (received_count > 0);

    // printf("Total recv()'ed %zu bytes.\n", received_total);
    return 0;
}
