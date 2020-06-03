#include "uchat.h"

static void create_main_window(GtkApplication *app, GtkWidget *window) {
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "uchat");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW (window), 1280, 720);
    gtk_widget_show_all(window);
}

static void activate (GtkApplication *app, gpointer user_data) {
  t_info *info = (t_info *)malloc(sizeof(t_info));

  create_main_window(app, info->main_window);
  info->back_image = mx_constructor_background_image(info->main_window, "Resources/huetaUpscale.jpg");
  mx_create_login_screen(info);
  if(user_data) {};
}


int main(int argc, char *argv[]) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("uchat.org", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
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
