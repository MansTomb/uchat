#include "client.h"

static void wrong_usage() {
    printf("Wrong Usage Client\n");
}

static int wrap(void *data) {
    t_info *info = data;

    mx_destroy(NULL, NULL, info);
    return 0;
}

static void reconnect(int *sockfd, t_info *info) {
    struct sockaddr_in serv_addr = info->sock->serv_addr;
    int i;

    for (i = 0; i < 10; ++i) {
        if (connect(*sockfd, (struct sockaddr*)&serv_addr,
            sizeof(serv_addr)) < 0) {
            printf("%u\n", serv_addr.sin_addr.s_addr);
            printf("%s", "Reconnecting...\n");
            close(*sockfd);
            *sockfd = socket(AF_INET, SOCK_STREAM, 0);
            sleep(3);
        }
        else
            break;
    }
    if (i == 10) {
        puts("\nGood bye, see you soon...\n");
        close(*sockfd);
        gdk_threads_add_idle(wrap, info);
    }
}

static void *read_from_server(void *info) {
    t_info *info1 = (t_info *)info;
    int n;
    char buff[MX_MAX_SEND_SIZE];
    char *responce = NULL;

    while (1) {
        if ((n = read(info1->sock->sock, buff, sizeof(buff))) <= 0) {
            if (info1->reconnect)
                reconnect(&info1->sock->sock, info1);
            else
                pthread_exit(0);
        }
        else if (n > 0) {
            mx_receive_message_handler(buff, &responce, info);
        }
        bzero(buff, sizeof(buff));
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        wrong_usage();
        exit(EXIT_FAILURE);
    }

    t_info *info = mx_create_info();

    info->sock = mx_client_socket_create(argv[1], atoi((argv[2])));
    gtk_init(&argc, &argv);
    mx_info_create_css(info);
    mx_login_screen_build(info, info->windows->log);
    pthread_create(&info->thread.data, NULL, &read_from_server, (void *)info);
    gtk_main();

    return 0;
}
