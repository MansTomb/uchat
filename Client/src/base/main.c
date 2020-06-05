#include "uchat.h"

static GtkWidget *create_main_window(GtkApplication *app) {
    GtkWidget *window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW (window), "uchat");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW (window), WIDTH, HEIGHT);
    gtk_widget_set_name(window, "main_window");
    return window;
}

static t_info *create_info(GtkApplication *app) {
    t_info *new = malloc(sizeof(t_info));
    GdkDisplay *display;
    GdkScreen *screen;

    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    new->main_window = create_main_window(app);
    new->layout = mx_layout_constructor("main_layout", WIDTH, HEIGHT);
    gtk_container_add(GTK_CONTAINER(new->main_window), new->layout);
    new->back_image = mx_constructor_background_image(new->main_window, BACKIMAGE_PATH);
    new->css = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(new->css), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    return new;
}

static void activate (GtkApplication *app, gpointer info) {
    info = create_info(app);

    mx_login_screen_create(info);
    if(info) {};
}


int main(int argc, char *argv[]) {
  GtkApplication *app;
  t_info *info = NULL;
  int status;

  app = gtk_application_new("uchat.org", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK (activate), info);
  status = g_application_run(G_APPLICATION (app), argc, argv);
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
