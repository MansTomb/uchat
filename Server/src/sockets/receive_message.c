#include "server.h"

int mx_recv_check(int n) {
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
    else if (n == 0)
        return -2;
    return 0;
}

int mx_receive_from_peer(t_info *info, t_peer *peer) {
    size_t received_count;

    received_count = recv(peer->socket, (char *)&peer->recv_buff,
                          MX_MAX_SEND_SIZE, MSG_DONTWAIT);
    if (received_count <= 0) {
        if (mx_recv_check(received_count) == -2)
            return -1;
    }
    return 0;
}
