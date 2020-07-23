#include "server.h"

static void send_one(t_sock *sock, t_peer *peer, int sd) {
    int n;

    n = send(sd, peer->send_buff, sizeof(peer->send_buff), MSG_DONTWAIT);
    if (n <= 0) {
        mx_send_check(sock, peer, n);
    }
}

static cJSON *create_piece_file(char *piece, char *path, int size) {
    cJSON *obj = cJSON_CreateObject();

    cJSON_AddNumberToObject(obj, "p_type", file);
    cJSON_AddStringToObject(obj, "piece", piece);
    cJSON_AddStringToObject(obj, "name", &path[strlen(MX_FILES_DIR)]);
    cJSON_AddNumberToObject(obj, "n", size);

    return obj;
}

static cJSON *send_first(cJSON *json, FILE *fp, char *path, int sd) {
    int size;
    cJSON *msg;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    msg = create_piece_file(cJSON_Print(json), path, size);

    return msg;
}

void mx_send_file(t_sock *sock, t_peer *peer, cJSON *bd, int sd) {
    char *path = cJSON_GetObjectItem(bd, "content")->valuestring;
    FILE *fp;
    int size;
    cJSON *msg;

    if ((fp = fopen(path, "rb")) == NULL)
        printf("Cannot open file on server.\n");
    else {
        printf("start sending file\n");
        msg = send_first(bd, fp, path, sd);
        mx_json_to_sending_buffer(peer->send_buff, msg);
        send_one(sock, peer, sd);
        // printf("%s\n", peer->send_buff);
        sleep(1);
        while (!feof(fp)) {
            fread(peer->send_buff, 1, MX_MAX_SEND_SIZE, fp);   // ->n
            // printf("---\n%s\n strlen = %d\n---", peer->send_buff, n);
            send_one(sock, peer, sd);
            bzero(peer->send_buff, sizeof(peer->send_buff));
        }
        printf("finish sending file\n");
        fclose (fp);
    }
}
