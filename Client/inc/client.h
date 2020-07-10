#pragma once

#include "uchat.h"
#include "defines_client.h"

typedef struct sockaddr_in t_saddr;
typedef struct s_info t_info;
typedef struct s_login t_login;
typedef struct s_register t_register;
typedef struct s_message t_message;
typedef struct s_message_img t_message_img;
typedef struct s_admin t_admin;
typedef struct s_preferences t_preferences;
typedef struct s_change_password t_change_password;
typedef struct s_chat t_chat;
typedef struct s_main_screen t_main_screen;
typedef struct s_profile t_profile;
typedef struct s_contact_add t_contact_add;
typedef struct s_group_create t_group_create;
typedef struct s_contacts t_contacts;
typedef struct s_exit t_exit;
typedef struct s_room_creation t_room_creation;
typedef struct s_windows t_windows;
typedef struct s_contact t_contact;
typedef struct s_profile_data t_profile_data;
typedef struct s_data t_data;
typedef struct s_sock t_sock;
typedef struct s_giter t_giter;
typedef struct s_user t_user;

struct s_giter {
    char *gname;
    GtkTreeIter iter;
};

// list of contacts that client have
struct s_contact {
    int cid;
    char *login;
    char *f_name;
    char *s_name;
    char *email;
    char *stat;
    int active;
    int grp_id;
    char *grp_name;
};

// client profile data
struct s_profile_data {
    int id;
    char *login;
    char *first_name;
    char *sec_name;
    char *user_email;
    char *status;

    int sound_noty;
    int vs_noty;
    int email_noty;
};

struct s_user {
    int id;
    char *login;
};

// struct that have access to all client data
struct s_data {
    t_profile_data *profile;

    t_list *contacts;
    t_list *cont_grp_names;
    t_list *tmp_users;
};

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
    GtkBuilder *builder;
    GtkWidget *main_fixed;
    GtkWidget *date_label;
    GtkWidget *name_label;
    GtkWidget *msg_bt;
    GtkWidget *menu;

    t_info *info;
};

struct s_message_img {
    GtkBuilder *builder;
    GtkWidget *main_fixed;
    GtkWidget *date_label;
    GtkWidget *name_label;
    GtkWidget *msg_bt;
    GtkWidget *menu;

    t_info *info;
};

struct s_login {
    GtkWidget *window;
    GtkBuilder *builder;
    GtkWidget *username_entry;
    GtkWidget *password_entry;
};

struct s_admin {
    GtkWidget *window;
    GtkBuilder *builder;
    GtkWidget *message_tv;
    GtkWidget *backbt;
    GtkWidget *sendbt;
};

struct s_register {
    GtkWidget *window;
    GtkBuilder *builder;
    GtkWidget *username_entry;
    GtkWidget *password_entry;
    GtkWidget *passwordc_entry;
};

struct s_preferences {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *box;
    GtkWidget *change_pass;
    GtkWidget *volume;
    GtkWidget *vnotify;
    GtkWidget *snotify;
    GtkWidget *enotify;
};

struct s_chat {
    char *chat_name;
    int cid;

    GtkBuilder *builder;
    GtkWidget *img_dialog;
    GtkWidget *main_box;
    GtkWidget *message_box;
    GtkWidget *entry;
    GtkFileFilter *ffilter;

    t_info *info;
};

struct s_main_screen {
    GtkWidget *window;
    GtkBuilder *builder;
    GtkWidget *revealer;
    GtkWidget *chat_stack;
    GtkWidget *menu_stack;
};

struct s_profile {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *box;
    GtkWidget *image;
    GtkWidget *avatartbt;
    GtkWidget *save;
    GtkWidget *edit;
    GtkWidget *cancel;
    GtkWidget *login;
    GtkWidget *fname;
    GtkWidget *lname;
    GtkWidget *email;
};

struct s_contact_add {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *addbt;
    GtkWidget *cancelbt;
    GtkWidget *entry;
    GtkWidget *combobox;
    GtkTreeStore *nameslist;

    t_info *info;
};

struct s_group_create {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *createbt;
    GtkWidget *cancelbt;
    GtkWidget *entry;

    t_info *info;
};

struct s_contacts {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *box;
    GtkWidget *addbt;
    GtkWidget *crtbt;
    GtkWidget *tree_view;
    GtkTreeStore *tree_store;
    GtkTreeViewColumn *log_col;
    GtkTreeViewColumn *stat_col;
    GtkCellRenderer *log_render;
    GtkCellRendererPixbuf *stat_render;

    GtkTreeIter main_iter;
    t_list *giters;
};

struct s_exit {
    GtkWidget *dialog;
    GtkWidget *fixed;
    GtkWidget *logout;
    GtkWidget *close;
};

struct s_room_creation {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *createbt;
    GtkWidget *cancelbt;
    GtkWidget *entry;
    GtkWidget *roomcheck;
    GtkWidget *channelcheck;

    t_info *info;
};

struct s_change_password {
    GtkWidget *dialog;
    GtkBuilder *builder;
    GtkWidget *changebt;
    GtkWidget *cancelbt;
    GtkWidget *oldpass;
    GtkWidget *newpass1;
    GtkWidget *newpass2;

    t_info *info;
};

struct s_windows {
    t_admin *adm;
    t_login *log;
    t_register *reg;
    t_main_screen *ms;
    t_profile *prof;
    t_contacts *cont;
    t_preferences *pref;
    t_room_creation *rc;
    t_contact_add *ac;
    t_change_password *cp;
    t_group_create *cg;
};

struct s_info {
    struct {
        pthread_t timer;
        pthread_t data;
    } thread;

    GtkWidget *main_window;
    GtkCssProvider *css;

    t_sock *sock;
    t_windows *windows;
    t_list *chat_list;
    gpointer current_window;

    char *response;
    cJSON *json;

    GTimer *timer;

    t_data *cl_data;

    gboolean wchange;
};

    /* Main */
t_info *mx_create_info();
void mx_info_create_css(t_info *new);

    /* Jsons */
void mx_save_login_data(t_info *info);
void mx_get_json_contacts(t_info *info);
void mx_get_json_chats_list(t_info *info);
void mx_chg_pass_json(t_info *info, const char *old_pass, const char *new_pass);
int mx_check_err_json(cJSON *new);

    /* Json wrappers */
bool mx_get_jtype(t_info *info, int type);
void mx_get_list_users_json_wrapper(t_info *info);
void mx_login_build_json_wrapper(t_info *info);
void mx_register_build_json_wrapper(t_info *info);
void mx_upd_prof_build_json_wrapper(t_info *info);

    /* Package transferring */
void mx_json_to_sending_buffer(char *buff, cJSON *json);
int mx_check_err_json(cJSON *new);

void mx_send_message_handler(cJSON *json, int sd);
void mx_receive_message_handler(char *receiving_buff, char **large_message,
                                t_info *info);
void mx_receive_file(cJSON *json, t_info *info);
void mx_send_file(cJSON *json, int sd);

    /* Sockets functions */
t_sock *mx_client_socket_create(char *ip, int port);

    /* UTILS FUNCTIONS */

    /* On exit */
gboolean mx_destroy(GtkWidget *widget, GdkEvent *event, gpointer data);

    /* Work with css */
void mx_css_from_file(t_info *info, char *filename);
void mx_css_from_data(t_info *info, char *data);

    /* Entrys */
GtkWidget *mx_entry_constructor(char *name);
bool mx_entry_text_exist(GtkWidget *entry);
const char *mx_entry_get_text(GtkWidget *entry);

    /* Toggle Button */
gboolean mx_get_tactive(GtkWidget *widget);

    /* Hash */
char *mx_create_hash(const char *pass);

    /* Json */
void mx_wait_for_json(t_info *info, int type1, int type2);
bool mx_get_jtype(t_info *info, int type);

    /* Dialog error */
void mx_dialog_warning_create(GtkWidget *parent, char *message);

    /* Set vnotify */
void mx_set_vnoti(t_main_screen *ms, char *chat_name, gboolean value);

/* Windows */

/*                             LOGIN SCREEN */
void mx_login_screen_build(t_info *info, t_login *log);
void mx_login_screen_destroy(t_info *info);

    /* Login callbacks */
void mx_on_click_register(GtkWidget *widget, gpointer data);

    /* Login error dialogs */
gboolean mx_login_data_validate(t_login *log);

/*                             REGISTER SCREEN */
void mx_register_screen_build(t_info *info, t_register *reg);
void mx_register_screen_destroy(t_info *info);


    /* Register callbacks */
void mx_on_click_back(GtkWidget *widget, gpointer data);

    /* Register error dialogs */
gboolean mx_reg_data_validate(t_register *reg);

/*                             Admin Screen */
void mx_admin_screen_build(t_info *info, t_admin *adm);
void mx_admin_screen_destroy(t_info *info);

/*  Callbacks */
void mx_on_send_everyone(GtkWidget *widget, gpointer data);
gboolean mx_admin_on_key_press(GtkWidget *widget, GdkEvent *event, gpointer data);

/*                             Main Chat Screen */
void mx_main_screen_build(t_info *info, t_main_screen *ms);
void mx_main_screen_destroy(t_info *info);

/*   Callbacks */
void mx_on_click_main_menu(GtkWidget *widget, gpointer data);
void mx_on_click_exit(GtkWidget *widget, gpointer data);

/*                              Profile Screen */
void mx_profile_build(t_info *info, t_profile *prof);
void mx_profile_destroy(t_info *info);

/* Callbacks */


/*                              Contacts screen */
void mx_contacts_build(t_info *info, t_contacts *cont);
void mx_contacts_destroy(t_info *info);
void mx_create_table(t_info *info, t_contacts *cont);
void mx_add_contact_build(t_info *info, t_contact_add *ac);
void mx_add_contact_destroy(t_info *info);

/*  Callbacks */
void mx_contacts_tree_on_click(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void mx_contacts_send_message(GtkWidget *widget, gpointer data);
void mx_contacts_delete(GtkWidget *widget, gpointer data);

void mx_on_add_contact_cancel(GtkWidget *widget, gpointer data);
void mx_on_add_contact_add(GtkWidget *widget, gpointer data);

void mx_create_group_build(t_info *info, t_group_create *cg);
void mx_create_group_destroy(t_info *info);

/*                              Room Creation */
void mx_room_creation_build(t_info *info, t_room_creation *rc);
void mx_room_creation_destroy(t_info *info);

    /* Callbacks */

    /* Validate data */
gboolean mx_room_creation_data_validation(t_room_creation *room);

/*                              Preferences Screen */

void mx_preferences_build(t_info *info, t_preferences *pref);
void mx_preferences_destroy(t_info *info);

    /* Callbacks */
void mx_on_click_theme_switch(GtkWidget *widget, gboolean state, gpointer data);
void mx_on_toggle_vnoti(GtkWidget *widget, gpointer data);
void mx_on_toggle_snoti(GtkWidget *widget, gpointer data);
void mx_on_toggle_enoti(GtkWidget *widget, gpointer data);
void mx_on_change_password(GtkWidget *widget, gpointer data);

/*                               Change Password */
void mx_change_password_build(t_info *info, t_change_password *cp);
void mx_change_password_destroy(t_info *info);
gboolean mx_cp_validate(t_change_password *cp);

    /* Callbacks */
void mx_on_cp_cancel(GtkWidget *widget, gpointer data);
void mx_on_cp_change(GtkWidget *widget, gpointer data);

/*                             CHAT SCREEN */
t_chat *mx_chat_build(t_info *info, char *chat_name, int cid);
void mx_chat_destroy(t_list_node *chat_node);
void mx_chat_put(t_info *info, char *chat_name, int cid);

    /* Chat callbacks */
void mx_send_message(GtkWidget *widget, gpointer data);

    /* Chat error dialogs */

/*                              Messages Class */
t_message *mx_message_build(t_info *info, char *username, char *msg);

    /* Message callbacks */
void mx_msg_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data);
void mx_msg_delete(GtkWidget *widget, gpointer data);

/*                              Messages Img Class */
t_message_img *mx_message_img_build(t_info *info, char *username, GtkWidget *img);

    /* Message callbacks */
void mx_msg_img_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data);
void mx_msg_img_delete(GtkWidget *widget, gpointer data);
