#include "client.h"

static void send_one(int sd, char *buff) {
    int n;

    n = send(sd, buff, MX_MAX_SEND_SIZE, MSG_DONTWAIT);
    if (n <= 0) {
        perror("write");
        pthread_exit((void *)EXIT_FAILURE);
    }
}

static cJSON *create_piece_file(char *piece, char *path, int size) {
    cJSON *obj = cJSON_CreateObject();

    int i;
    for (i = strlen(path) - 1; i > 0; i--) {
        if (path[i - 1] == '/')
            break;
    }
    cJSON_AddNumberToObject(obj, "p_type", 3);
    cJSON_AddStringToObject(obj, "piece", piece);
    cJSON_AddStringToObject(obj, "name", &path[i]);
    cJSON_AddNumberToObject(obj, "n", size);

    return obj;
}

static void send_first(cJSON *json, FILE *fp, char *path, int sd) {
    int size;
    char buff[MX_MAX_SEND_SIZE];
    cJSON *msg;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    msg = create_piece_file(cJSON_Print(json), path, size);
    mx_json_to_sending_buffer(buff, msg);
    if (send(sd, buff, strlen(buff), MSG_DONTWAIT) <= 0) {
        perror("write");
        pthread_exit((void *)EXIT_FAILURE);
    }
}

void mx_send_file(cJSON *json, int sd) {
    FILE *fp;
    char *path = cJSON_GetObjectItem(json, "content")->valuestring;
    char buff[MX_MAX_SEND_SIZE];
    cJSON *msg;

    if ((fp = fopen(path, "rb")) == NULL)
        printf("Cannot open file on client.\n");
    else {
        printf("start sending file\n");
        send_first(json, fp, path, sd);
        sleep(1);
        while (!feof(fp)) {
            int n = fread(buff, 1, MX_MAX_SEND_SIZE, fp);   // ->n
            send_one(sd, buff);
            bzero(buff, sizeof(buff));
        }
        printf("finish sending file\n");
        fclose (fp);
    }
}
