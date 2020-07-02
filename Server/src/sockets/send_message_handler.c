#include "server.h"

static int send_check(t_sock *sock, t_peer *client, int n) {
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("Peer is not ready right now, try again later.\n");
        }
        else {
            perror("Send() from peer error");
            mx_handle_disconnect(sock, client);
        }
    }
    // we have read as many as possible
    // else if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
    //     return -1;
    // }
    else if (n == 0) {
        printf("Peer can't accept data right now, try again later.\n");
        // return -1;
    }
    return 0;
}

static void send_one(t_sock *sock, t_peer *peer, int sd, char *buff) {
    int n;

    n = send(sd, buff, strlen(buff), MSG_DONTWAIT);
    if (n <= 0) {
        send_check(sock, peer, n);
    }
}

static cJSON *create_peice(int type, char *str) {
    cJSON *obj = cJSON_CreateObject();

    cJSON_AddNumberToObject(obj, "p_type", type);
    cJSON_AddStringToObject(obj, "piece", str);

    return obj;
}

void mx_send_message_handler(t_sock *sock, t_peer *peer, cJSON *bd, int sd) {
    char *root = cJSON_Print(bd);
    mx_print_serv_out(bd, root);
    char send_buff[1024];

    if (strlen(root) < 1000) {
        mx_json_to_sending_buffer(send_buff, create_peice(0, root));
        send_one(sock, peer, sd, send_buff);
    }
    else {
        peer->large_message = malloc((strlen(root) + 1) * sizeof(char));
        sprintf(peer->large_message, "%s", root);

        sprintf(peer->sending_buffer, "lalala");
        send_one(sock, peer, sd, send_buff);

        // считувати з буфера і відправляти пакетами

        // mx_print_serv_out(bd, peer->large_message);
        mx_strdel(&peer->large_message);
    }
}
