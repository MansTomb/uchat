#pragma once

#include "uchat.h"

typedef struct s_background_image {
    GtkWidget *window;
    GtkWidget *layout;
    GtkWidget *image;
    GdkPixbuf *pixbuf;
} t_background_image;

typedef struct s_info {
    GtkWidget *main_window;

    t_background_image *back_image;
} t_info;

void mx_create_login_screen(t_info *info);

t_background_image *mx_constructor_background_image(GtkWidget *window, char *image_path);
void mx_show_background_image(t_background_image *back_image);
void mx_delete_background_image(t_background_image *back_image);
