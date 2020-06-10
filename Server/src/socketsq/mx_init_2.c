#include "server.h"

void mx_set_nonblock_for_stdin(void) {
    int flag;

    flag = fcntl(STDIN_FILENO, F_GETFL, 0);
    flag |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flag);
}

char *mx_init_buff_set_zero(int buffsize) {
    char *new = NULL;

    new = (char *)malloc(buffsize * sizeof(char));
    if (!new) {
        perror("Server: init: malloc error");
        return NULL;
    }
    memset(new, '\0', buffsize);
    return new;
}

void mx_perror_and_exit(char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}
