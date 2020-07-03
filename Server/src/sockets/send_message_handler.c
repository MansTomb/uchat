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
    char *large_message;

    // mx_print_serv_out(bd, root);

    char send_buff[1024];
    // printf("root = %lu\n", strlen(root));

    if (strlen(root) < 1000) {
        mx_json_to_sending_buffer(send_buff, create_peice(0, root));
        send_one(sock, peer, sd, send_buff);
    }
    else {
        large_message = strdup(root);
        printf("large_message size = %lu\n", strlen(large_message));
        // printf("message = %s\n", large_message);

        unsigned long i = 0;
        while (large_message[i]) {
            char str[512];
            bzero(str, strlen(str));
            strncpy(str, &large_message[i], 511);

            i += strlen(str);
            printf("i = %lu\n", i);
            if (i == strlen(large_message)) {
                mx_json_to_sending_buffer(send_buff, create_peice(2, str));
                send_one(sock, peer, sd, send_buff);
                break;
            }
            else {
                mx_json_to_sending_buffer(send_buff, create_peice(1, str));
                send_one(sock, peer, sd, send_buff);
            }
        }
        mx_strdel(&large_message);
    }
}
