#include "server.h"

static void file_loop(t_info *info, t_peer *peer, FILE *new, int fsize) {
    char buff[MX_MAX_SEND_SIZE];
    int n;

    while (1) {
        // bzero(peer->recv_buff, sizeof(peer->recv_buff));
        if ((n = recv(peer->socket, buff, MX_MAX_SEND_SIZE, 0)) < 0) {
            // printf("\n~~handle_disconnect~~\n");
            mx_handle_disconnect(info->sock, peer);
        }
        else if (n > 0){
            // printf("\n---\n%s\nfsize = %d, n = %d\n---\n", buff, fsize, n);
            if (fsize <= MX_MAX_SEND_SIZE) {
                fwrite(buff, 1, fsize, new);
                break;
            }
            fwrite(buff, 1, n, new);
            fsize -= MX_MAX_SEND_SIZE;
        }
        else {
            printf("\n~~~unused behavior~~~\n");
            break;
        }
    }
}

void mx_receive_file(t_info *info, t_peer *peer, cJSON *json) {
    FILE *new = NULL;
    char *name = cJSON_GetObjectItem(json, "name")->valuestring;
    char *fullname = mx_strjoin(MX_FILES_DIR, name);
    int fsize = cJSON_GetObjectItem(json, "n")->valueint;

    printf("name = %s, full = %s, size = %d\n", name, fullname, fsize);
    if ((new = fopen(fullname, "wb")) == NULL)
        printf("Cannot open file on client.\n");
    else {
        printf("recv file opened\n");
        file_loop(info, peer, new, fsize);
    }
    fclose (new);
    mx_strdel(&fullname);
    printf("recv file closed\n");
}
