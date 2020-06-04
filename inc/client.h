#pragma once

#include "uchat.h"

typedef struct s_background_image {
    GtkWidget *window;
    GtkWidget *image;
    GdkPixbuf *pixbuf;
} t_background_image;

typedef struct s_info {
    GtkWidget *main_window;
    GtkWidget *layout;

    GtkCssProvider *css;

    t_background_image *back_image;

    gpointer current_window;
} t_info;

typedef struct s_login {
    GtkWidget *loginbt;
    GtkWidget *registerbt;

    GtkWidget *username_label;
    GtkWidget *password_label;

    GtkWidget *username_entry;
    GtkWidget *password_entry;
} t_login;

/* UTILS FUNCTIONS */

    /* Work with background images */
t_background_image *mx_constructor_background_image(GtkWidget *window, char *image_path);
void mx_background_image_show(t_info *info);
void mx_background_image_delete(t_background_image *back_image);

    /* Work with buttons */
GtkWidget *mx_button_constuctor(char *label, char *button_name);
void mx_button_delete(GtkWidget *button);

    /* Work with entry(input bar) */
GtkWidget *mx_entry_constructor(char *name);

    /* Work with grids */
GtkWidget *mx_grid_constructor(char *name, int width, int height);

    /* Work with layouts */
GtkWidget *mx_layout_constructor(char *name, int width, int height);

    /* Work with css */
void mx_css_from_file(t_info *info, char *filename);
void mx_css_from_data(t_info *info, char *data);

    /* Work with labels */
GtkWidget *mx_label_constructor(char *name, char *text);

/* LOGIN SCREEN */
void mx_login_screen_create(t_info *info);

    /* Login callbacks */
void login_on_click(GtkApplication *app, gpointer user_data);
void register_on_click(GtkApplication *app, gpointer user_data);
