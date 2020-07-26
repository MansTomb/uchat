#pragma once

#include "uchat.h"

/*    Defines for widgets placement */
#define WIDTH 1280
#define HEIGHT 720

#define MX_MAX_SEND_SIZE 4096

/*    Define for укорачивания(не нашёл англ слова в голове) */
#define MX_BOX_V GTK_ORIENTATION_VERTICAL
#define MX_CB G_CALLBACK
#define MX_GSIG_CON g_signal_connect

#define MX_PASS_NONPRINT "Password contain non printable characters!"
#define MX_NONPRINT "Not valid characters in field!!"
#define MX_NEWPASS_NOTEQUAL "New password wont match!"
#define MX_FIELDS_NOTEMPTY "Fields cant be empty!"
#define MX_CNEXIST_OR_LOGIN "The contact does not exist or this is your login!"
#define MX_USE_OR_GRP_EMPTY "Contact username or group cant be empty!"
#define MX_MSGLEN "Message cant be longer than 100 chars!"

#define MX_MSGHEIGHT(msg) (strlen(msg) + 20 * 10)
#define MX_MSGWIDTH(msg) (strlen(msg) * 4 > 400 ? 400 : strlen(msg) * 4)

#define MX_SEND_FILES_DIR "Client/files_send/"
#define MX_RECV_FILES_DIR "Client/files_recv/"
#define MX_ONLINE "./Resources/images/online.png"
#define MX_OFFLINE "./Resources/images/offline.png"
#define MX_SNOTIFY "./Resources/sounds/message.mp3"

#define MX_GLADE_AC "./Resources/glade/add_contact.glade"
#define MX_GLADE_CM "./Resources/glade/contact_move.glade"
#define MX_GLADE_ADMIN "./Resources/glade/admin_screen.glade"
#define MX_GLADE_BAN "./Resources/glade/ban_user.glade"
#define MX_GLADE_CHAT "./Resources/glade/chat.glade"
#define MX_GLADE_CONT "./Resources/glade/contacts.glade"
#define MX_GLADE_CG "./Resources/glade/create_group.glade"
#define MX_GLADE_LOGIN "./Resources/glade/login_screen.glade"
#define MX_GLADE_REG "./Resources/glade/register_screen.glade"
#define MX_GLADE_MS "./Resources/glade/main_chat_screen.glade"
#define MX_GLADE_MSG "./Resources/glade/message.glade"
#define MX_GLADE_MSGIMG "./Resources/glade/message_img.glade"
#define MX_GLADE_OTPROF "./Resources/glade/other_user_profile.glade"
#define MX_GLADE_PREF "./Resources/glade/preferences.glade"
#define MX_GLADE_CP "./Resources/glade/change_pass.glade"
#define MX_GLADE_DP "./Resources/glade/del_profile.glade"
#define MX_GLADE_PROF "./Resources/glade/profile.glade"
#define MX_GLADE_RC "./Resources/glade/room_creation.glade"
#define MX_GLADE_UNBAN "./Resources/glade/unban_user.glade"

#define MX_STRDEL(str) (MX_MALLOC_SIZE(str) > 0 ? free(str) : (void)0)

/* Types for sending jsons */
typedef enum {
    make_register,
    failed_register,                // when login exists in db
    success_register,               // --

    make_authorization,
    failed_authorization,           // --
    success_authorization,          // when login exists in db in 1 example, and login and hash valid

    make_delete_user,
    failed_delete_user,
    success_delete_user,

    make_change_password,
    failed_change_password,         // --
    success_change_password,        // valid hash

    make_update_profile,
    success_update_profile,
    failed_update_profile,

    get_client_contacts,
    failed_client_contacts,
    success_client_contacts,

    get_client_chats,
    send_client_chats,

    get_client_chat_messages,
    send_client_chat_messages,

    make_search_user,
    failed_search_user,             // error db
    success_search_user,

    make_add_new_contact,
    failed_add_new_contact,
    success_add_new_contact,

    make_del_contact,
    failed_del_contact,         // when contact doesn't exist in contacts_list
    success_del_contact,

    make_add_contact_group,
    failed_add_contact_group,
    success_add_contact_group,

    make_change_contact_group,
    failed_change_contact_group,
    success_change_contact_group,

    make_del_contact_group,
    failed_del_contact_group,
    success_del_contact_group,

    make_new_personal_chat,
    failed_new_personal_chat,
    success_new_personal_chat,

    send_message,
    failed_send_message,                    // error db

    edit_message,
    delete_message,
    failed_edit_delete_message,             // error db

    logout,

    make_new_group_chat_channel,
    failed_new_group_chat_channel,
    success_new_group_chat_channel,

    make_add_user_in_chat,
    failed_add_user_in_chat,
    success_add_user_in_chat,
    add_user_in_chat_return_chat,

    make_block_user,
    failed_block_user,
    success_block_user,

    make_unblock_user,
    failed_unblock_user,
    success_unblock_user,

    make_leave_chat,
    failed_leave_chat,
    success_leave_chat,

    this_uid_login,   // два єнама без запроса
    this_uid_logout,

    superuser_message,

    file_msg,
    failed_receiving_file,
} t_actions;
