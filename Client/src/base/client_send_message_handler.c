#include "client.h"

void mx_json_to_sending_buffer(char *buff, cJSON *json) {
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

    bzero(send_buff, MX_MAX_SEND_SIZE);
    if (cJSON_GetObjectItem(json, "json_type")->valueint == file_msg) {
        mx_send_file(json, sd);
    }
    else {
        if (strlen(buff) < 3 * MX_MAX_SEND_SIZE / 2) {
            mx_json_to_sending_buffer(send_buff, create_peice(0, buff));
            send_one(sd, send_buff);
        }
        else {
            printf("еще нет\n");
        }
    }
}
