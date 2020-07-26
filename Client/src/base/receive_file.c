#include "client.h"

static void file_loop(t_info *info, FILE *new, int fsize) {
    char buff[MX_MAX_SEND_SIZE];
    int n;

    while (1) {
        bzero(buff, sizeof(buff));
        if ((n = read(info->sock->sock, buff, MX_MAX_SEND_SIZE)) <= 0) {
            puts("\nGood bye, see you soon...\n");
            pthread_exit(0);
        }
        else if (n > 0) {
            if (fsize <= MX_MAX_SEND_SIZE) {
                fwrite(buff, 1, fsize, new);
                break;
            }
            fwrite(buff, 1, n, new);
            fsize -= MX_MAX_SEND_SIZE;
        }
    }
}

static void info_handler(char *str, t_info *info) {
    if (mx_handle_if_not_requested(info, cJSON_Parse(str)))
        info->json = cJSON_Parse(str);
    printf("Responce: %s\n", str);
}

void mx_receive_file(cJSON *json, t_info *info) {
    FILE *new = NULL;
    char *name = cJSON_GetObjectItem(json, "name")->valuestring;
    char *fullname = mx_strjoin(MX_RECV_FILES_DIR, name);
    int fsize = cJSON_GetObjectItem(json, "n")->valueint;

    printf("name = %s, full = %s, size = %d\n", name, fullname, fsize);
    if ((new = fopen(fullname, "wb")) == NULL)
        printf("Cannot open file on client.\n");
    else {
        printf("recv file opened\n");
        file_loop(info, new, fsize);
    }
    fclose (new);
    info_handler(cJSON_GetObjectItem(json, "piece")->valuestring, info);
    // сохранить гдето в инфо что файл получен
    mx_strdel(&fullname);
    printf("recv file closed\n");
}
