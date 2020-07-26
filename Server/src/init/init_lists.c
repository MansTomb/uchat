#include "server.h"

static void read_line(char **list, FILE *fp) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i;

    for (i = 0; i < MX_LIST_SIZE; ++i) {
        if ((read = getline(&line, &len, fp)) == -1) {
            printf("Anime file smaller than 100 lines.\n");
            // mx_del_strarr(&list);
            // mx_shutdown_server;
            exit(1);
        }
        list[i] = strdup(line);
    }
    list[i] = NULL;
    if (line)
        free(line);
}

static void init_list(char *path, char **socklist) {
    FILE *fp;
    char buff[1024];
    int n = 0;

    if ((fp = fopen(path, "r")) == NULL)
        printf("Cannot open list file on server.\n");
    else {
        read_line(socklist, fp);
        fclose (fp);
    }
    printf("%s lists created\n", path);
}

void mx_init_lists(t_sock *sock) {
    init_list(MX_ANIME_LIST_DIR, sock->anime_list);
    init_list(MX_JOKES_LIST_DIR, sock->joke_list);
}
