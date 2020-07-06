#include "client.h"

#define MX_MAX_SEND_SIZE 4096

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

void mx_send_message_handler(cJSON *json, int sd) {
    char send_buff[MX_MAX_SEND_SIZE];
    char *buff = cJSON_Print(json);

    if (strlen(buff) < 3 * MX_MAX_SEND_SIZE / 2) {
        json_to_sending_buffer(send_buff, create_peice(0, buff));
        send_one(sd, send_buff);
    }
    else {
        printf("еще нет\n");
    }
}
