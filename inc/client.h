#pragma once

#include "uchat.h"
#include "defines_client.h"

typedef struct sockaddr_in t_saddr;

typedef struct s_sock {
    int sock;
    int valread;

    t_saddr serv_addr;
} t_sock;
typedef struct s_background_image {
    GtkWidget *window;
    GtkWidget *image;
    GdkPixbuf *pixbuf;
} t_background_image;

typedef struct s_login {
    GtkWidget *loginbt;
    GtkWidget *registerbt;

    GtkWidget *username_label;
    GtkWidget *username_entry;

    GtkWidget *password_label;
    GtkWidget *password_entry;

    t_background_image *back_image;
} t_login;

typedef struct s_register {
    GtkWidget *registerbt;
    GtkWidget *backbt;

    GtkWidget *username_label;
    GtkWidget *username_entry;

    GtkWidget *password_label;
    GtkWidget *password_entry;

    GtkWidget *password2_label;
    GtkWidget *password2_entry;

    t_background_image *back_image;
} t_register;

typedef struct s_chat {
    GtkWidget *stack;
    GtkWidget *stack_controller;
    GtkWidget *layout;
    GtkWidget *scroll;

    t_background_image *back_image;
} t_chat;

typedef struct s_windows {
    t_login *log;
    t_register *reg;
    t_chat *chat;
} t_windows;


typedef struct s_info {
    GtkWidget *main_window;
    GtkWidget *layout;

    GtkCssProvider *css;

    t_sock *sock;
    t_windows *windows;
    gpointer current_window;
} t_info;

/* Main */
GtkWidget *create_main_window(GtkApplication *app);
t_info *create_info(GtkApplication *app);

/* Jsons */
json_value *mx_login_build_json(t_info *info);


/* Sockets functions */
t_sock *mx_client_socket_create(char *ip, int port);

/* UTILS FUNCTIONS */

    /* Work with widgets */
void mx_widget_destroy(GtkWidget *widget);

    /* Work with background images */
t_background_image *mx_background_image_constructor(t_info *info, char *image_path);
void mx_background_image_show(t_background_image *backimg);
void mx_background_image_hide(t_background_image *backimg);
void mx_background_image_delete(t_background_image *back_image);

    /* Work with buttons */
GtkWidget *mx_button_constuctor(char *label, char *button_name);
void mx_button_delete(GtkWidget *button);

    /* Work with entry(input bar) */
GtkWidget *mx_entry_constructor(char *name);
bool mx_entry_text_exist(GtkWidget *entry);
const char *mx_entry_get_text(GtkWidget *entry);

    /* Work with grids */
GtkWidget *mx_grid_constructor(char *name, int width, int height);

    /* Work with layouts */
GtkWidget *mx_layout_constructor(char *name, int width, int height);
void mx_layout_put(GtkWidget *layout, GtkWidget *obj, int width, int height);

    /* Work with css */
void mx_css_from_file(t_info *info, char *filename);
void mx_css_from_data(t_info *info, char *data);

    /* Work with labels */
GtkWidget *mx_label_constructor(char *name, char *text);

    /* Work with dialog windows */
void mx_dialog_warning_create(GtkWidget *parent, char *message);

    /* Work with scrollable */
GtkWidget *mx_scrollable_constructor(char *name, GtkAdjustment *hadj, GtkAdjustment *vadj);


/* Windows */


/*                             LOGIN SCREEN */
t_login *mx_login_constructor(t_info *info);
void mx_login_screen_show(t_info *info);
void mx_login_screen_hide(t_info *info);

    /* Login callbacks */
void login_on_click(GtkApplication *app, gpointer user_data);
void register_on_click(GtkApplication *app, gpointer user_data);

    /* Login error dialogs */
void mx_login_entry_empty(t_info *info);

/*                             REGISTER SCREEN */
t_register *mx_register_constructor(t_info *info);
void mx_register_screen_show(t_info *info);
void mx_register_screen_hide(t_info *info);

    /* Register callbacks */
void back_to_login_on_click(GtkApplication *app, gpointer user_data);
void reg_user_on_click(GtkApplication *app, gpointer user_data);

    /* Register error dialogs */


/*                             CHAT SCREEN */
t_chat *mx_chat_constructor(t_info *info);
void mx_chat_screen_show(t_info *info);
void mx_chat_screen_hide(t_info *info);

    /* Chat callbacks */


    /* Chat error dialogs */
