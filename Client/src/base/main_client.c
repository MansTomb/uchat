#include "client.h"

struct sockaddr_in serv_addr;

static void reconnect(int sockfd) {
    struct sockaddr addr;
    socklen_t clientlen;
    int i;

    printf("%s","Lost connection to the server\n");
    getpeername(sockfd, (struct sockaddr*)&addr, (socklen_t *)&clientlen);
    for (i = 0; i < 10; ++i) {
        if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("%s", "Reconnecting...\n");
            sleep(3);
        }
        else
            break;
    }
    if (i == 10) {
        puts("\nGood bye, see you soon...\n");
        close(sockfd);
        exit(0);
    }
}
// -----------------------------------------

static void *read_from_server(void *sock) {   //----------------- READ
    int sockfd = *(int *)sock;
    int n;
    char buff[MX_MAX_SEND_SIZE];
    char *large_message = NULL;

    while (1) {
        if ((n = recv(sockfd, buff, sizeof(buff), 0)) <= 0)
            reconnect(sockfd);
        else {
            // printf("%s\n", buff);
            mx_receive_message_handler(buff, &large_message);
        }
    }
    pthread_exit(0);
}

static void *write_to_server(void *sock) {   //----------------- WRITE
    int sockfd = *(int *)sock;
    int n;
    char buff[MX_MAX_SEND_SIZE];

    while (1) {
        fgets(buff, sizeof(buff), stdin);
        cJSON *json = cJSON_Parse(buff);
        if (mx_check_err_json(json))
            puts(buff);     // вивід в термінал
        else
            mx_send_message_handler(json, sockfd);
        // mx_perror_and_exit(MX_ERR_CL_WR);
    }
    pthread_exit(0);
}

// void catch_ctrl_c_and_exit(int sig) {
//     if (sig) {}
//     puts("\nGood bye, see you soon...\n");
//     exit(EXIT_SUCCESS);
// }

int main(int argc, char *argv[]) {
    int sockfd = 0;
    // int n = 0;
    char buff[512];
    pthread_t read_thread;
    pthread_t write_thread;

    if(argc != 3)
        return (printf("client") * 0 + 1);

    // signal(SIGINT, catch_ctrl_c_and_exit);

    /*  check localhost name, if server and clients are deployed on the same machine
     *  the local host name should be 'localhost'.
     */
    // if (strcmp(argv[1], "localhost")==0) {
    //     char hostname[1024];
    //     hostname[1023] = "\0";
    //     gethostname(hostname, 1023);
    //     server_host = gethostbyname(hostname);
    //     if (server_host==NULL) {
    //         error("ERROR unable to resolve hostname");
    //     }
    // }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return (printf("socket") * 0 + 1);

    bzero((char *)&serv_addr, sizeof(serv_addr));
    bzero(buff, sizeof(buff));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // printf("sin.fam = %hhu\nsin.port = %hu\nsockfd = %d\n",
    //         serv_addr.sin_family, serv_addr.sin_port, sockfd);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
        return (printf("error") * 0 + 1);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
       return (printf("error") * 0 + 1);

    pthread_create(&read_thread, NULL, &read_from_server, (void *)&sockfd);
    pthread_create(&write_thread, NULL, &write_to_server, (void *)&sockfd);
    pthread_join(read_thread, NULL);
    // pthread_join(write_thread, NULL);
    // if (!(pthread_join(write_thread, NULL)))
    //     pthread_cancel(read_thread);
    // else
    //     pthread_join(read_thread, NULL);

    close(sockfd);

    return 0;
}
