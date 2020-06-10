#pragma once

#include "uchat.h"
#include "defines_client.h"

#define MX_MSGHEIGHT(msg) (strlen(msg) + 10 + mx_count_substr(message, "\n") * 20)

typedef struct sockaddr_in t_saddr;
typedef struct s_sock t_sock;
typedef struct s_background_image t_background_image;
typedef struct s_message t_message;
typedef struct s_login t_login;
typedef struct s_register t_register;
typedef struct s_chat t_chat;
typedef struct s_chat_switcher t_chat_switcher;
typedef struct s_windows t_windows;
typedef struct s_main_menu t_main_menu;
typedef struct s_profile t_profile;
typedef struct s_contacts t_contacts;
typedef struct s_room_creation t_room_creation;
typedef struct s_info t_info;

struct s_sock {
    int sock;
    int valread;

    t_saddr serv_addr;
};
struct s_background_image {
    GtkWidget *image;
    GdkPixbuf *pixbuf;
};

struct s_message {
    GtkWidget *button;
    GtkWidget *lable;
    // GtkWidget *layout;
    GtkWidget *frame;
    GtkWidget *menu;

    t_info *info;

    // GtkWidget *event;
};

struct s_login {
    GtkWidget *loginbt;
    GtkWidget *registerbt;

    GtkWidget *username_label;
    GtkWidget *username_entry;

    GtkWidget *password_label;
    GtkWidget *password_entry;

    t_background_image *back_image;
};

struct s_register {
    GtkWidget *registerbt;
    GtkWidget *backbt;

    GtkWidget *username_label;
    GtkWidget *username_entry;

    GtkWidget *password_label;
    GtkWidget *password_entry;

    GtkWidget *password2_label;
    GtkWidget *password2_entry;

    t_background_image *back_image;
};

struct s_chat {
    GtkWidget *scroll;
    GtkWidget *box;

    GtkWidget *sendbt;
    GtkWidget *msgentry;

    t_list *messages;

    t_info *info;
    bool showed_chat;
};

struct s_chat_switcher {
    GtkWidget *box;
    t_chat *chat;
};

struct s_main_menu {
    GtkWidget *box;

    GtkWidget *profile;
    GtkWidget *contancts;
    GtkWidget *create_room;
    GtkWidget *preferences;
    GtkWidget *exit;

    GtkWidget *back;
};

struct s_windows {
    t_login *log;
    t_register *reg;
    t_chat_switcher *chat_switcher;
    t_profile *profile;
    t_contacts *contacts;
    t_room_creation *room_creation;
    t_main_menu *main_menu;
};

struct s_profile {
    GtkWidget *image;
    GtkWidget *namelabel;
    GtkWidget *name;
    GtkWidget *idlabel;
    GtkWidget *id;

    GtkWidget *edit;
    GtkWidget *save;
    GtkWidget *cancel;

    GtkWidget *scrollable;
    GtkWidget *layout;
};

struct s_contacts {
    GtkWidget *treeview;
};

struct s_room_creation {
    GtkWidget *dialog;
    GtkWidget *groupbt;
    GtkWidget *channelbt;

    GtkWidget *create;
    GtkWidget *cancel;

    GtkWidget *type;
    GtkWidget *entry;
};

struct s_info {
    GtkWidget *main_window;
    GtkWidget *layout;

    GtkCssProvider *css;

    t_sock *sock;
    t_windows *windows;
    t_list *chat_list;
    gpointer current_window;
};

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
void mx_layout_put(GtkWidget *layout, GtkWidget *obj, guint width, guint height);

    /* Work with css */
void mx_css_from_file(t_info *info, char *filename);
void mx_css_from_data(t_info *info, char *data);

    /* Work with labels */
GtkWidget *mx_label_constructor(char *name, char *text);

    /* Work with dialog windows */
void mx_dialog_warning_create(GtkWidget *parent, char *message);

    /* Work with scrollable */
GtkWidget *mx_scrollable_constructor(char *name, gint width, gint height);
void mx_scrollable_container_add(GtkWidget *scroll, GtkWidget *child);

    /* Work with stack switcher */
GtkWidget *mx_stack_switcher_constructor(char *name, GtkWidget *stack);

    /* Work with stack */
GtkWidget *mx_stack_constructor(char *name);
void mx_stack_add(GtkWidget *stack, GtkWidget *child, char *name, char *title);

    /* Work with fixed */
GtkWidget *mx_fixed_constructor(char *name, gint widht, gint height);
void mx_fixed_put(GtkWidget *fixed, GtkWidget *widget, gint x, gint y);

    /* Work with frames */
GtkWidget *mx_frame_constructor(char *name, char *label, gint w, gint h);

    /* Work with box */
GtkWidget *mx_box_constructor(char *name, gint widht, gint height, GtkOrientation orientaion);

    /* Work with listbox */
GtkWidget *mx_listbox_constructor(char *name);


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



/*                             Main Chat Screen */
void mx_main_chat_screen_show(t_info *info);
void mx_main_chat_screen_hide(t_info *info);


/*                              Main Menu */
t_main_menu *mx_main_menu_constructor(t_info *info);
void mx_main_menu_show(t_info *info);
void mx_main_menu_hide(t_info *info);

void mx_find_and_hide_screen(t_info *info);

    /* Callbacks */
void mx_on_click_profile(GtkWidget *widget, gpointer data);
void mx_on_click_contacts(GtkWidget *widget, gpointer data);
void mx_on_click_create_room(GtkWidget *widget, gpointer data);
void mx_on_click_preferences(GtkWidget *widget, gpointer data);
void mx_on_click_exit(GtkWidget *widget, gpointer data);
void mx_on_click_back(GtkWidget *widget, gpointer data);

/*                              Profile Screen */
t_profile *mx_profile_constructor(t_info *info);
void mx_profile_show(t_info *info);
void mx_profile_hide(t_info *info);

    /* Callbacks */
void mx_on_click_profile_edit(GtkWidget *widget, gpointer *data);
void mx_on_click_profile_save(GtkWidget *widget, gpointer *data);
void mx_on_click_profile_cancel(GtkWidget *widget, gpointer *data);

/*                              Room Creation */
t_room_creation *mx_room_creation_constructor(t_info *info);
void mx_room_creation_destructor(t_info *info);

    /* Callbacks */
void mx_on_click_create_room_channel(GtkWidget *widget, gpointer data);
void mx_on_click_create_room_group(GtkWidget *widget, gpointer data);
void mx_on_click_create_room_create(GtkWidget *widget, gpointer data);
void mx_on_click_create_room_cancel(GtkWidget *widget, gpointer data);

/*                             CHAT SCREEN */
t_chat *mx_chat_constructor(t_info *info);
void mx_chat_screen_show(t_chat *chat);
void mx_chat_screen_hide(t_chat *chat);
void mx_chat_message_put(t_chat *chat, t_message *message);
void mx_chat_show_message(t_message *message);
void mx_chat_hide_message(t_message *message);

    /* Chat callbacks */
void mx_send_message(GtkWidget *widget, gpointer data);

    /* Chat error dialogs */

    /* Chat switcher */
t_chat_switcher *mx_chat_switcher_constructor(t_info *info);
void mx_chat_switcher_add_chat(t_info *info, t_chat *chat, char *chat_name);
void mx_chat_switcher_show(t_info *info);
void mx_chat_switcher_hide(t_info *info);

void mx_hide_chat(GtkWidget *widget, gpointer data); // Show chat in switcher. Не перепутать с show_chat_screen
void mx_show_chat(GtkWidget *widget, gpointer data); // Show chat in switcher. Не перепутать с show_chat_screen

/*                              Messages Class */
t_message *mx_message_construct(t_info *info, char *message, char *username);

    /* Message callbacks */
void mx_callback_reply(GtkWidget *widget, gpointer data);
void mx_callback_forward(GtkWidget *widget, gpointer data);
void mx_callback_delete(GtkWidget *widget, gpointer data);
void mx_callback_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data);
