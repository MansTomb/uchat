#include "server.h"

int mx_delete_peer(t_peer *peer) {
    close(peer->socket);
    mx_delete_message_queue(&peer->send_buffer);
    return 0;
}

int mx_create_peer(t_peer *peer) {
    mx_create_message_queue(MX_MAX_MESSAGES_BUFFER_SIZE, &peer->send_buffer);

    peer->current_sending_byte = -1;
    peer->current_receiving_byte = 0;

    return 0;
}

char *mx_peer_get_addres_str(t_peer *peer) {
    static char res[INET_ADDRSTRLEN + 10];
    socklen_t *addrlen = NULL;

    getpeername(peer->socket, (struct sockaddr *)&peer->addres,
                (socklen_t *)addrlen);
    sprintf(res, "%s:%d",
            inet_ntoa(peer->addres.sin_addr), ntohs(peer->addres.sin_port));

    return res;
}

int mx_peer_add_to_send(t_peer *peer, t_message *message) {
    return mx_enqueue(&peer->send_buffer, message);
}
