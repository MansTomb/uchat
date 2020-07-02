#include "client.h"

void mx_prepare_to_send(char *buff) {

    cJSON *obj = cJSON_CreateObject();
    cJSON_AddNumberToObject(obj, "p_type", 0);
    cJSON_AddStringToObject(obj, "piece", buff);

    char *root = cJSON_Print(obj);
    sprintf(buff, "%s", root);

}

struct sockaddr_in serv_addr;

static void *read_from_server(void *sock) {
    int sockfd = *(int *)sock;
    int n, i;
    char buff[1024];
    struct sockaddr addr;
    socklen_t clientlen;

    while (1) {
        if ((n = read(sockfd, buff, sizeof(buff))) <= 0) {
            printf("%s","Lost connection to the server\n");
            getpeername(sockfd, (struct sockaddr*)&addr, (socklen_t *)&clientlen);
            for (i = 0; i < 10; ++i) {
                if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
                    printf("%s", "Reconnecting...\n");
                    sleep(3);
                }
                else {
                    break;
                }
            }
            if (i == 10) {
                puts("\nGood bye, see you soon...\n");
                close(sockfd);
                exit(0);
            }
        }
        // mx_perror_and_exit(MX_ERR_CL_RE);
        puts(buff);
        bzero(buff, sizeof(buff));
    }
    pthread_exit(0);
}

static void *write_to_server(void *sock) {
    int sockfd = *(int *)sock;
    int n;
    char buff[1024];

    // cJSON *obj = cJSON_CreateObject();
    // cJSON_AddNumberToObject(obj, "json_type", 3);
    // cJSON_AddStringToObject(obj, "login", "trohalska");
    // cJSON_AddStringToObject(obj, "hash", "000");

    // char *string = cJSON_Print(obj);
    // cJSON_Delete(obj);

    // cJSON *obj2 = cJSON_CreateObject();
    // cJSON_AddNumberToObject(obj2, "p_type", 0);
    // cJSON_AddStringToObject(obj2, "piece",
    //     "{ \"json_type\": 3, \"login\": \"ooo\", \"hash\": \"222\"}");

    // char *string2 = cJSON_Print(obj2);

    // if (string2 == NULL)
    //     fprintf(stderr, "Failed to print.\n");
    // else {
    //     sprintf(buff, "%s", string2);
    //     printf("%s", buff);
    //     write(sockfd, buff, sizeof(buff));
    // }
    // cJSON_Delete(obj2);

    while (1) {
        fgets(buff, sizeof(buff), stdin);
        if (!strncmp(buff, "/quit", 5)) {
            close(sockfd);
            break;
        }

        mx_prepare_to_send(buff);

        if ((n = write(sockfd, buff, sizeof(buff))) <= 0) {
            perror("write");
            pthread_exit((void *)EXIT_FAILURE);
        }
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
    char recvbuff[1024];
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
    bzero(recvbuff, sizeof(recvbuff));
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
