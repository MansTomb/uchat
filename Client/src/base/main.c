#include "client.h"


static void wrong_usage(GtkApplication *app, gpointer data) {
    printf("Wrong Usage Client\n");
    if (app && data) {};
}

// static void *read_from_server(void *info) {
//     t_info *info1 = (t_info *)info;
//     int n;
//     char buff[1024];

//     while (1) {
//         if ((n = read(info1->sock->sock, buff, sizeof(buff))) < 0) {
//             // perror(MX_ERR_CL_RE);
//             puts("\nGood bye, see you soon...\n");
//             pthread_exit(0);
//         }
//         else if (n > 0) {
//             // mx_perror_and_exit(MX_ERR_CL_RE);
//             t_message *one = mx_message_construct(buff, "loh");
            
//             mx_chat_message_put((t_chat *)mx_get_index(info1->chat_list, 0)->data, one);
//         }
//         bzero(buff, sizeof(buff));
//     }
//     pthread_exit(0);
// }

static void open_app(GtkApplication *app, GFile **files, gint n_file, gchar *hint, gpointer sock) {
    if (n_file != 2) {
        wrong_usage(app, sock);
        exit(EXIT_FAILURE); // nado bude funka uni4tozitel
    }
    t_info *info = mx_create_info(app);

    info->sock = mx_client_socket_create(g_file_get_basename(files[0]), atoi(g_file_get_basename(files[1])));
    // mx_login_screen_show(info);
    info->windows->chat_switcher = mx_chat_switcher_constructor(info);

    // mx_push_front(info->chat_list, mx_chat_constructor(info));
    // mx_push_front(info->chat_list, mx_chat_constructor(info));

    // mx_chat_switcher_add_chat(info, (t_chat *)mx_get_index(info->chat_list, 0)->data, "general");
    // mx_chat_switcher_add_chat(info, (t_chat *)mx_get_index(info->chat_list, 1)->data, "new");

    // t_message *one = mx_message_construct(info, text, "Loh1");
    // t_message *one2 = mx_message_construct(info, text2, "Loh1");
    // t_message *one3 = mx_message_construct(info, text3, "Heh");

    // mx_chat_screen_show((t_chat *)mx_get_index(info->chat_list, 1)->data);
    // pthread_t read_thread;
    // pthread_create(&read_thread, NULL, &read_from_server, (void *)info);
        // pthread_join(read_thread, NULL);

    // mx_chat_message_put((t_chat *)mx_get_index(info->chat_list, 0)->data, one);
    // mx_chat_message_put((t_chat *)mx_get_index(info->chat_list, 1)->data, one2);
    // mx_chat_message_put((t_chat *)mx_get_index(info->chat_list, 0)->data, one3);

    mx_main_chat_screen_show(info);
    // mx_show_main_hide_screen(info);

    if(sock && files && n_file && hint) {};
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
