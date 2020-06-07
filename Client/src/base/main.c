#include "client.h"


static void wrong_usage(GtkApplication *app, gpointer data) {
    printf("Wrong Usage Client\n");
    if (app && data) {};
}

static void open_app(GtkApplication *app, GFile **files, gint n_file, gchar *hint, gpointer sock) {
    if (n_file != 2) {
        wrong_usage(app, sock);
        exit(EXIT_FAILURE); // nado bude funka uni4tozitel
    }
    t_info *info = create_info(app);

    info->sock = mx_client_socket_create(g_file_get_basename(files[0]), atoi(g_file_get_basename(files[1])));
    // mx_login_screen_show(info);
    info->windows->chat_switcher = mx_chat_switcher_constructor(info);

    mx_push_front(info->chat_list, mx_chat_constructor(info));
    mx_push_front(info->chat_list, mx_chat_constructor(info));

    mx_chat_switcher_add_chat(info, (t_chat *)mx_get_index(info->chat_list, 0)->data, "general", "General");
    mx_chat_switcher_add_chat(info, (t_chat *)mx_get_index(info->chat_list, 1)->data, "new", "new");
    mx_chat_screen_show((t_chat *)mx_get_index(info->chat_list, 0)->data);
    mx_chat_screen_show((t_chat *)mx_get_index(info->chat_list, 1)->data);
    mx_chat_show_message((t_chat *)mx_get_index(info->chat_list, 0)->data, "Lo", "privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara privet koshara");
    mx_chat_show_message((t_chat *)mx_get_index(info->chat_list, 1)->data, "Lo", ".messageframe label {\n    color: white;\n    text-shadow: 10px 10px 10px black, 1px 1px 1px turquoise;\n    font-size: 40px;\n}");

    if(sock && files && n_file && hint) {};
}

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("uchat.org", G_APPLICATION_HANDLES_OPEN);
    g_signal_connect(app, "open", G_CALLBACK(open_app), NULL);
    g_signal_connect(app, "activate", G_CALLBACK(wrong_usage), NULL);
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
