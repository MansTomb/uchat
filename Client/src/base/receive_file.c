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
            // printf("\n---\n%s\nn = %d\n---\n", buff, fsize);
            if (fsize <= MX_MAX_SEND_SIZE) {
                fwrite(buff, 1, fsize, new);
                break;
            }
            fwrite(buff, 1, n, new);
            fsize -= MX_MAX_SEND_SIZE;
        }
    }
}

void mx_receive_file(cJSON *json, t_info *info) {
    FILE *new = NULL;
    char *name = cJSON_GetObjectItem(json, "name")->valuestring;
    char *fullname = mx_strjoin(MX_FILES_DIR, name);
    int fsize;

    if ((new = fopen(fullname, "wb")) == NULL)
        printf("Cannot open file on client.\n");
    else {
        fsize = cJSON_GetObjectItem(json, "n")->valueint;
        printf("opened, size = %d\n", fsize);
        file_loop(info, new, fsize);
    }
    fclose (new);
    // сохранить гдето в инфо что файл получен
    mx_strdel(&fullname);
    printf("file closed\n");
}
