#include "client.h"

static void wrong_usage() {
    printf("Wrong Usage Client\n");
}

static void *read_from_server(void *info) {
    t_info *info1 = (t_info *)info;
    int n;
    char buff[1024];

    while (1) {
        if ((n = read(info1->sock->sock, buff, sizeof(buff))) < 0) {
            // perror(MX_ERR_CL_RE);
            puts("\nGood bye, see you soon...\n");
            pthread_exit(0);
        }
        else if (n > 0) {
            info1->response = strdup(buff);
            info1->json = cJSON_Parse(buff);
            printf("Responce: %s\n", info1->response);
        }
        bzero(buff, sizeof(buff));
    }
    pthread_exit(0);
}

static void *login_timeout(void *data) {
    t_info *info = data;
    info->timer = g_timer_new();

    while (1) {
        // printf("Time left for timeout: %d\n", 60 - (int)g_timer_elapsed(info->timer, NULL));
        if (g_timer_elapsed(info->timer, NULL) > 60) {
            printf("leave\n");
            pthread_kill(info->thread.data, 0);
            gtk_main_quit();
        }
        if (!g_timer_is_active(info->timer))
            pthread_exit(0);
        sleep(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        wrong_usage();
        exit(EXIT_FAILURE); // nado bude funka uni4tozitel
    }

    t_info *info = mx_create_info();
    info->sock = mx_client_socket_create(argv[1], atoi((argv[2])));

    gtk_init(&argc, &argv);

    mx_login_screen_build(info, info->windows->log);
    // mx_main_screen_build(info, info->windows->ms);
    // mx_chat_put(info, "Best Chat");

    pthread_create(&info->thread.data, NULL, &read_from_server, (void *)info);
    pthread_create(&info->thread.timer, NULL, &login_timeout, (void *)info);

    gtk_main();

    return 0;
}
