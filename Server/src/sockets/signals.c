#include "server.h"

static void shutdown_pr(int code) {
    printf("Shutdown server properly.\n");
    exit(code);
}

static void handle_signal_action(int sig_number) {
    if (sig_number == SIGINT) {
        printf("\nSIGINT was catched!\n");
        shutdown_pr(EXIT_SUCCESS);
    }
    else if (sig_number == SIGPIPE) {
        printf("\nSIGPIPE was catched!\n");
        // shutdown_pr(EXIT_SUCCESS);
    }
    else if (sig_number == SIGSEGV) {
        printf("\nSIGSEGV was catched!\n");
        shutdown_pr(EXIT_SUCCESS);
    }
}

int mx_setup_signals(void) {
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
    if (sigaction(SIGSEGV, &sa, 0) != 0) {
        perror("sigaction()");
        return -1;
    }
    return 0;
}
