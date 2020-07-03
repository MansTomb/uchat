#include "server.h"

static void json_to_sending_buffer(char *buff, cJSON *json) {
    char *root;

    root = cJSON_Print(json);
    sprintf(buff, "%s", root);
}

static void send_one(int sd, char *buff) {
    int n;

    n = send(sd, buff, strlen(buff), MSG_DONTWAIT);
    if (n <= 0) {
        perror("write");
        pthread_exit((void *)EXIT_FAILURE);
    }
}

static cJSON *create_peice(int type, char *str) {
    cJSON *obj = cJSON_CreateObject();

    cJSON_AddNumberToObject(obj, "p_type", type);
    cJSON_AddStringToObject(obj, "piece", str);

    return obj;
}

void mx_send_message_handler(char *buff, int sd) {
    char send_buff[1024];

    if (strlen(buff) < 1000) {
        json_to_sending_buffer(send_buff, create_peice(0, buff));
        send_one(sd, send_buff);
    }
    else {

        // peer->large_message = malloc((strlen(root) + 1) * sizeof(char));
        // sprintf(peer->large_message, "%s", root);

        // sprintf(peer->sending_buffer, "lalala");
        // send_one(sock, peer, sd, send_buff);

        // // считувати з строки і відправляти пакетами через буфер

        // mx_strdel(&peer->large_message);
    }
}
