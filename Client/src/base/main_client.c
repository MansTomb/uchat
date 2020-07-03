#include "client.h"

// ---------------------------------------------------------------------------- RECEIVE

int mx_check_err_json(cJSON *new) {
    const char *error_ptr;

    if (new == NULL)
        if ((error_ptr = cJSON_GetErrorPtr()) != NULL) {
            fprintf(stderr, "cJSON_Parse error, before: %s", error_ptr);
            return 1;
        }
    return 0;
}

static void one_message_handler(char *receiving_buff) { // переробити під клієнт Антона
    cJSON *json = cJSON_Parse(receiving_buff);
    if (mx_check_err_json(json))
        return;

    puts(receiving_buff);         // вивід в термінал

    bzero(receiving_buff, strlen(receiving_buff));
}

static void large_message_handler(cJSON *json, char *large_message) { // переробити під клієнт Антона
    int ptype = cJSON_GetObjectItem(json, "p_type")->valueint;
    char *piece;
    cJSON *all_json;

    if (ptype == 1 || ptype == 2) {
        piece = cJSON_GetObjectItem(json, "piece")->valuestring;
        large_message = mx_strjoin_free(large_message, piece);

        if (ptype == 2) {
            printf("large = %s\n", large_message);
            all_json = cJSON_Parse(large_message);
            if (mx_check_err_json(all_json))
                return;

            puts(large_message);  // вивід в термінал

            mx_strdel(&large_message);
            cJSON_Delete(all_json);
        }
    }
    else
        printf("ERROR large_message_handler\n");
}

void mx_receive_message_handler(char *receiving_buff, char *large_message) {
    cJSON *json;
    int type;

    json = cJSON_Parse(receiving_buff);
    if (mx_check_err_json(json)) {
        puts(receiving_buff);     // вивід в термінал
        return;
    }
    type = cJSON_GetObjectItem(json, "p_type")->valueint;
    if (type == 0) {            // обробка одного повідомлення розміром до 1024
        one_message_handler(cJSON_GetObjectItem(json, "piece")->valuestring);
    }
    else if (type == 1 || type == 2) {  // обробка одного повідомлення великого розміру
        puts(receiving_buff);
        puts("111\n");
        large_message_handler(json, large_message);
    }
    else {
        printf("ERROR type\n");
    }
    cJSON_Delete(json);
}

// ---------------------------------------------------------------------------- SEND


static void json_to_sending_buffer(char *buff, cJSON *json) {
    char *root;

    root = cJSON_Print(json);
    sprintf(buff, "%s", root);
}

static void send_one(int sd, char *buff) {
    int n;

    n = send(sd, buff, strlen(buff), MSG_DONTWAIT);
    if (n <= 0) {
        perror("write");
        pthread_exit((void *)EXIT_FAILURE);
    }
}

static cJSON *create_peice(int type, char *str) {
    cJSON *obj = cJSON_CreateObject();

    cJSON_AddNumberToObject(obj, "p_type", type);
    cJSON_AddStringToObject(obj, "piece", str);

    return obj;
}

void mx_send_message_handler(char *buff, int sd) {
    char send_buff[1024];

    if (strlen(buff) < 1000) {
        json_to_sending_buffer(send_buff, create_peice(0, buff));
        send_one(sd, send_buff);
    }
    else {

        // peer->large_message = malloc((strlen(root) + 1) * sizeof(char));
        // sprintf(peer->large_message, "%s", root);

        // sprintf(send_buff, "lalala");
        // send_one(sock, peer, sd, send_buff);

        // // считувати з строки і відправляти пакетами через буфер

        // mx_strdel(&peer->large_message);
    }
}

// ---------------------------------------------------------------------------- MAIN

struct sockaddr_in serv_addr;

static void *read_from_server(void *sock) {
    int sockfd = *(int *)sock;
    int n, i;
    char buff[1024];
    char *large_message = NULL;
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
        else {
            // puts(buff);
            mx_receive_message_handler(buff, large_message);
        }
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
        mx_send_message_handler(buff, sockfd);
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
