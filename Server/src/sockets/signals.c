#include "server.h"

static void shutdown_properly(int code) {
    // int i;

    //----- получть инфу для закрытия сокетов

    // close(listen_sock);
    // for (i = 0; i < MAX_CLIENTS; ++i)
    //     if (connection_list[i].socket != NO_SOCKET)
    //     close(connection_list[i].socket);

    printf("Shutdown server properly.\n");
    exit(code);
}

static void handle_signal_action(int sig_number) {
    if (sig_number == SIGINT) {
        printf("\nSIGINT was catched!\n");
        shutdown_properly(EXIT_SUCCESS);
    }
    else if (sig_number == SIGPIPE) {
        printf("\nSIGPIPE was catched!\n");
        shutdown_properly(EXIT_SUCCESS);
    }
}

int mx_setup_signals() {
    struct sigaction sa;

    sa.sa_handler = handle_signal_action;
    if (sigaction(SIGINT, &sa, 0) != 0) {
        perror("sigaction()");
        return -1;
    }
    if (sigaction(SIGPIPE, &sa, 0) != 0) {
        perror("sigaction()");
        return -1;
    }

    return 0;
}
