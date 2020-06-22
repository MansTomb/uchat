#include "client.h"


static void wrong_usage(GtkApplication *app, gpointer data) {
    printf("Wrong Usage Client\n");
    if (app && data) {};
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

static void destor_all(t_info *info) {
    pthread_kill(info->thread.data, 0);
    gtk_widget_destroy(info->layout);
    gtk_window_close(GTK_WINDOW(info->main_window));
}

static void *login_timeout(void *data) {
    t_info *info = data;
    info->timer = g_timer_new();

    while (1) {
        // printf("Time left for timeout: %d\n", 60 - (int)g_timer_elapsed(info->timer, NULL));
        if (g_timer_elapsed(info->timer, NULL) > 60) {
            printf("leave\n");
            destor_all(info);
        }
        if (!g_timer_is_active(info->timer))
            pthread_exit(0);
        sleep(1);
    }
}

static void open_app(GtkApplication *app, GFile **files, gint n_file, gchar *hint, gpointer sock) {
    if (n_file != 2) {
        wrong_usage(app, sock);
        exit(EXIT_FAILURE); // nado bude funka uni4tozitel
    }
    t_info *info = mx_create_info(app);
    info->sock = mx_client_socket_create(g_file_get_basename(files[0]), atoi(g_file_get_basename(files[1])));
    mx_login_screen_show(info);
    pthread_create(&info->thread.data, NULL, &read_from_server, (void *)info);
    pthread_create(&info->thread.timer, NULL, &login_timeout, (void *)info);
}

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("uchat.org", G_APPLICATION_HANDLES_OPEN);
    MX_GSIG_CON(app, "open", MX_CB(open_app), NULL);
    MX_GSIG_CON(app, "activate", MX_CB(wrong_usage), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref (app);

    return status;
}

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
