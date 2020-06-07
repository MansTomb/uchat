#include "server.h"

int mx_delete_peer(t_peer *peer) {
    close(peer->socket);
    // delete_message_queue(&peer->send_buffer);
    return 0;
}

int mx_create_peer(t_peer *peer) {
    mx_create_message_queue(MAX_MESSAGES_BUFFER_SIZE, &peer->send_buffer);

    peer->current_sending_byte = -1;
    peer->current_receiving_byte = 0;

    return 0;
}

// char *peer_get_addres_str(peer_t *peer)
// {
//   static char ret[INET_ADDRSTRLEN + 10];
//   char peer_ipv4_str[INET_ADDRSTRLEN];
//   inet_ntop(AF_INET, &peer->addres.sin_addr, peer_ipv4_str, INET_ADDRSTRLEN);
//   sprintf(ret, "%s:%d", peer_ipv4_str, peer->addres.sin_port);

//   return ret;
// }

// int peer_add_to_send(peer_t *peer, message_t *message)
// {
//   return enqueue(&peer->send_buffer, message);
// }
