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
typedef struct s_invite_user t_invite_user;
typedef struct s_ban_user t_ban_user;
typedef struct s_unban_user t_unban_user;
typedef struct s_main_screen t_main_screen;
typedef struct s_profile t_profile;
typedef struct s_other_profile t_other_profile;
typedef struct s_contact_add t_contact_add;
typedef struct s_group_create t_group_create;
typedef struct s_contacts t_contacts;
typedef struct s_exit t_exit;
typedef struct s_room_creation t_room_creation;
typedef struct s_delete_profile t_delete_profile;
typedef struct s_windows t_windows;
typedef struct s_contact t_contact;
typedef struct s_profile_data t_profile_data;
typedef struct s_data t_data;
typedef struct s_sock t_sock;
typedef struct s_giter t_giter;
typedef struct s_user t_user;
typedef struct s_del_msg t_del_msg;
typedef struct s_edit_msg t_edit_msg;
typedef struct s_send_msg t_send_msg;
typedef struct s_send_msg_img t_send_msg_img;
typedef struct s_group t_group; // json
typedef struct s_chat_member t_chat_member;

struct s_chat_member {
    char *login;
    int uid;
};

struct s_group {
    int id;
    char *name;
};

struct s_giter {
    char *gname;
    int id;
    GtkTreeIter iter;
};

struct s_del_msg {
    t_info *info;
    t_chat *chat;
    t_message *msg;
    int mid;
    int i;
};
struct s_edit_msg {
    char *content;
    t_info *info;
    t_chat *chat;
    t_message *msg;
};
struct s_send_msg {
    int cid;
    t_message *msg;
    t_chat *chat;
    t_info *info;
};

struct s_send_msg_img {
    int cid;
    t_message_img *msg;
    t_chat *chat;
    t_info *info;
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

    int mid;
    int cid;

    t_info *info;
};

struct s_message_img {
    GtkBuilder *builder;
    GtkWidget *main_fixed;
    GtkWidget *date_label;
    GtkWidget *name_label;
    GtkWidget *msg_bt;
    GtkWidget *menu;

    int mid;
    int cid;

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
    GtkWidget *del_prof;
    GtkWidget *volume;
    GtkWidget *vnotify;
    GtkWidget *snotify;
    GtkWidget *enotify;
    GtkWidget *themeswitch;
};

struct s_chat {
    char *chat_name;
    int cid;
    int ctype;
    int role;
    bool edit;
    t_message *editedmsg;
    t_list *msg_list;

    GtkBuilder *builder;
    GtkWidget *img_dialog;
    GtkWidget *main_box;
    GtkWidget *message_box;
    GtkWidget *entry;
    GtkFileFilter *ffilter;
    GtkWidget *banbt;
    GtkWidget *unbanbt;
    GtkWidget *invbt;
    GtkWidget *leavebt;

    t_list *users;

    t_info *info;
};

struct s_invite_user {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *entry;
    
    t_info *info;
    t_chat *chat;
};

struct s_ban_user {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *entry;
    
    t_info *info;
    t_chat *chat;
};

struct s_unban_user {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *entry;
    
    t_info *info;
    t_chat *chat;
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

struct s_other_profile {
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *image;
    GtkWidget *login;
    GtkWidget *fname;
    GtkWidget *lname;
    GtkWidget *email;

    t_info *info;
};

struct s_delete_profile {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *pass1;
    GtkWidget *pass2;

    t_info *info;
};

struct s_contact_add {
    GtkBuilder *builder;
    GtkWidget *dialog;
    GtkWidget *addbt;
    GtkWidget *cancelbt;
    GtkWidget *entry;
    GtkWidget *combobox;
    GtkTreeStore *nameslist;
    GtkEntryCompletion *e_comp;

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
    GtkWidget *menu;
    GtkWidget *gmenu;
    GtkTreeStore *tree_store;
    GtkTreeViewColumn *log_col;
    GtkTreeViewColumn *stat_col;
    GtkCellRenderer *log_render;
    GtkCellRendererPixbuf *stat_render;

    char *clicked_cont;
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
    t_delete_profile *dp;
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
bool mx_handle_if_not_requested(t_info *info, cJSON *json);

    /* Sounds */

    /* Handlers */
void mx_handle_delete_message(t_info *info, cJSON *json);
void mx_handle_edit_message(t_info *info, cJSON *json);
void mx_handle_send_message(t_info *info, cJSON *json);
void mx_handle_invite_user(t_info *info, cJSON *json);

    /* Jsons */
void mx_save_login_data(t_info *info);
void mx_save_chat_users(t_chat *chat, const cJSON *users);
void mx_get_json_contacts(t_info *info);
void mx_get_json_chats_list(t_info *info);
void mx_upd_groups_list(const t_info *info);
void mx_send_json_group(t_info *info, const char *gname);
void mx_chg_pass_json(t_info *info, const char *old_pass, const char *new_pass);
int mx_check_err_json(cJSON *new);
void mx_start_chat_json(t_info *info);
int mx_get_cnt_id_by_login(const char *login, t_list *list);
void mx_invite_json_wrapper(t_invite_user *inv);

    /* t_data clear */
void mx_clr_custom_lst(t_list *list);
void mx_clr_profile(t_profile_data *p, int type);
void mx_del_cnt_json(t_info *info);

    /* Json wrappers */
bool mx_get_jtype(t_info *info, int type);
void mx_get_list_users_json_wrapper(t_info *info);
void mx_login_build_json_wrapper(t_info *info);
void mx_register_build_json_wrapper(t_info *info);
void mx_upd_prof_build_json_wrapper(t_info *info);
void mx_add_cnt_json_wrapper(t_contact_add *ac);
void mx_send_message_t1_json_wrapper(t_chat *chat, char *content);
void mx_send_message_t2_json_wrapper(t_chat *chat, char *content);
void mx_edit_message_t1_json_wrapper(t_message *msg, char *content);
void mx_delete_message_t1_json_wrapper(t_message *msg);
void mx_get_json_chat_history(t_info *info, t_chat *chat);
void mx_create_room_wrap(t_info *info);
void mx_delete_user_wrapper(t_info *info);

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

t_chat *mx_find_chat(t_info *info, int cid);
t_message *mx_find_message(t_chat *chat, int mid);
GtkWidget *mx_gobject_builder(GtkBuilder *builder, char *name);

gboolean mx_validate_chars(char *text);

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
void mx_set_vnoti(t_info *info, t_main_screen *ms, int cid, gboolean value);

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
GtkWidget *mx_create_menu(t_info *info);
GtkWidget *mx_create_gmenu(t_info *info);
void mx_create_table(t_info *info, t_contacts *cont);
void mx_add_contact_build(t_info *info, t_contact_add *ac);
void mx_add_contact_destroy(t_info *info);
void mx_other_profile_build(t_info *info, t_contact *cont);

/*  Callbacks */
void mx_contacts_tree_on_click(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void mx_contacts_open_prof(GtkWidget *widget, gpointer data);
void mx_contacts_send_message(GtkWidget *widget, gpointer data);
void mx_contacts_move(GtkWidget *widget, gpointer data);
void mx_contacts_delete(GtkWidget *widget, gpointer data);

void mx_on_add_contact_cancel(GtkWidget *widget, gpointer data);
void mx_on_add_contact_add(GtkWidget *widget, gpointer data);

void mx_create_group_build(t_info *info, t_group_create *cg);
void mx_create_group_destroy(t_info *info);

void mx_on_crt_group_cancel(GtkWidget *widget, gpointer data);
void mx_on_crt_group_create(GtkWidget *widget, gpointer data);

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

/*                                Delete Profile */
void mx_delete_profile_build(t_info *info, t_delete_profile *dp);
void mx_delete_profile_destroy(t_info *info);

    /* Callbacks */
void mx_del_profile_cancel(GtkWidget *widget, gpointer data);
void mx_del_profile_delete(GtkWidget *widget, gpointer data);

/*                             CHAT SCREEN */
t_chat *mx_chat_build(t_info *info, cJSON *json);
void mx_chat_destroy(t_info *info, int cid);
void mx_chat_put(t_info *info, cJSON *json);
void mx_invite_user_build(t_info *info, t_chat *chat);
void mx_invite_user_destroy(t_invite_user *inv);
void mx_ban_user_build(t_info *info, t_chat *chat);
void mx_ban_user_destroy(t_ban_user *ban);
void mx_unban_user_build(t_info *info, t_chat *chat);
void mx_unban_user_destroy(t_unban_user *unban);

void mx_message_put(t_info *info, t_message *msg, int cid);
void mx_message_img_put(t_info *info, t_message_img *msg, int cid);

    /* Chat callbacks */
void mx_send_message(GtkWidget *widget, gpointer data);
void mx_on_scroll_edge(GtkWidget *widget, GtkPositionType pos, gpointer data);
gboolean mx_chat_stack_click(GObject *gobject, GParamSpec *pspec, gpointer user_data);
void mx_unban_user(GtkWidget *widget, gpointer data);
void mx_left_room(GtkWidget *widget, gpointer data);
void mx_ban_user(GtkWidget *widget, gpointer data);
void mx_invite_user(GtkWidget *widget, gpointer data);
void mx_unban_cancel(GtkWidget *widget, gpointer data);
void mx_unban_ban(GtkWidget *widget, gpointer data);
void mx_ban_cancel(GtkWidget *widget, gpointer data);
void mx_ban_ban(GtkWidget *widget, gpointer data);

    /* Chat error dialogs */

/*                              Messages Class */
t_message *mx_message_build(t_info *info, cJSON *json, int cid);
void mx_message_destroy(t_chat *chat, t_message *msg);

    /* Message callbacks */
void mx_msg_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data);
void mx_msg_delete(GtkWidget *widget, gpointer data);

/*                              Messages Img Class */
t_message_img *mx_message_img_build(t_info *info, cJSON *json, int cid);

    /* Message callbacks */
void mx_msg_img_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data);
void mx_msg_img_delete(GtkWidget *widget, gpointer data);
