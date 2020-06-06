#include "client.h"


// static void wrong_usage(GtkApplication *app, gpointer data) {
//     printf("Wrong Usage Client\n");
//     if (app && data) {};
// }

// static void open_app(GtkApplication *app, GFile **files, gint n_file, gchar *hint, gpointer sock) {
//     if (n_file != 2) {
//         wrong_usage(app, sock);
//         exit(EXIT_FAILURE); // nado bude funka uni4tozitel
//     }
//     t_info *info = create_info(app);

//     info->sock = mx_client_socket_create(g_file_get_basename(files[0]), atoi(g_file_get_basename(files[1])));

//     mx_login_screen_create(info);

//     if(sock && files && n_file && hint) {};
// }

// int main(int argc, char *argv[]) {
//     GtkApplication *app;
//     int status;

//     app = gtk_application_new("uchat.org", G_APPLICATION_HANDLES_OPEN);
//     g_signal_connect(app, "open", G_CALLBACK(open_app), NULL);
//     g_signal_connect(app, "activate", G_CALLBACK(wrong_usage), NULL);
//     status = g_application_run(G_APPLICATION(app), argc, argv);
//     g_object_unref (app);
//     return status;
// }

// int main(int argc, char *argv[]) {
//    if(argc) {};
//    int sock = 0, valread;
//    struct sockaddr_in serv_addr;
//    char *hello = "Hello from client";
//    char buffer[1024] = {0};
//    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//    {
//       printf("\n Socket creation error \n");
//       return -1;
//    }

//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_port = htons(atoi(argv[2]));

//    // Convert IPv4 and IPv6 addresses from text to binary form
//    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
//    {
//       printf("\nInvalid address/ Address not supported \n");
//       return -1;
//    }

//    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
//    {
//       printf("\nConnection Failed \n");
//       return -1;
//    }
//    send(sock , hello , strlen(hello) , 0 );
//    printf("Hello message sent\n");
//    valread = read( sock , buffer, 1024);
//    printf("%s\n",buffer );
//    return 0;
// }

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------


static void *read_from_server(void *sock) {
    int sockfd = *(int *)sock;
    int n;
    char buff[1024];

    while (1) {
        if ((n = read(sockfd, buff, sizeof(buff))) < 0) {
            // perror(MX_ERR_CL_RE);
            puts("\nGood bye, see you soon...\n");
            pthread_exit(0);
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

    while (1) {
        fgets(buff, sizeof(buff), stdin);
        if (!strncmp(buff, "/quit", 5)) {
            close(sockfd);
            break;
        }
        if ((n = write(sockfd, buff, sizeof(buff))) < 0) {
            perror("client loop: write error");
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
    struct sockaddr_in serv_addr;
    pthread_t read_thread;
    pthread_t write_thread;

    if(argc != 3)
        return (printf("usage: ./uchat <server IP> <network port>\n") * 0 + 1);

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
        return (printf("client: socket creation error\n") * 0 + 1);

    bzero((char *)&serv_addr, sizeof(serv_addr));
    bzero(recvbuff, sizeof(recvbuff));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // printf("sin.fam = %hhu\nsin.port = %hu\nsockfd = %d\n",
    //         serv_addr.sin_family, serv_addr.sin_port, sockfd);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
        return (printf("client: inet_pton error occured\n") * 0 + 1);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
       return (printf("client: connection failed\n") * 0 + 1);

    pthread_create(&read_thread, NULL, &read_from_server, (void *)&sockfd);
    pthread_create(&write_thread, NULL, &write_to_server, (void *)&sockfd);
    pthread_join(read_thread, NULL);
    pthread_join(write_thread, NULL);
    // if (!(pthread_join(write_thread, NULL)))
    //     pthread_cancel(read_thread);
    // else
    //     pthread_join(read_thread, NULL);

    close(sockfd);

    return 0;
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------
