#include "client.h"

static void wrong_usage() {
    printf("Wrong Usage Client\n");
}

static void reconnect(int *sockfd, t_info *info) {
    // struct sockaddr addr;
    // socklen_t clientlen;
    struct sockaddr_in serv_addr = info->sock->serv_addr;
    int i;

    printf("%s","Lost connection to the server\n");
    // int name = getpeername(sockfd, (struct sockaddr*)&addr, (socklen_t *)&clientlen);
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
        mx_destroy(NULL, NULL, info);
        // exit(0);   //destroy && exit
    }
}

static void *read_from_server(void *info) {
    t_info *info1 = (t_info *)info;
    int n;
    char buff[MX_MAX_SEND_SIZE];
    char *responce = NULL;

    while (1) {
        if ((n = read(info1->sock->sock, buff, sizeof(buff))) <= 0) {
            reconnect(&info1->sock->sock, info1);
        }
        else if (n > 0) {
            mx_receive_message_handler(buff, &responce, info);
        }
        bzero(buff, sizeof(buff));
    }
    pthread_exit(0);
}

static void *read_from_stdin(void *info) {   // for testing server
    t_info *info1 = (t_info *)info;
    int n;
    char buff[MX_MAX_SEND_SIZE];
    char *responce = NULL;

    while (1) {
        fgets(buff, sizeof(buff), stdin);
        cJSON *json = cJSON_Parse(buff);
        if (mx_check_err_json(json))
            puts(buff);     // вивід в термінал
        else
            mx_send_message_handler(json, info1->sock->sock);
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
            mx_destroy(NULL, NULL, info);
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
    mx_info_create_css(info);

    mx_login_screen_build(info, info->windows->log);

    pthread_create(&info->thread.data, NULL, &read_from_server, (void *)info);
    // // g_idle_add(read_from_server, info);
    // info->thread.data = g_thread_new("read", read_from_server, info);
    pthread_create(&info->thread.timer, NULL, &login_timeout, (void *)info);

    // pthread_create(&info->thread.data, NULL, &read_from_stdin, (void *)info);  // for testing server

    gtk_main();

    return 0;
}
