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
#define MX_NEWPASS_NOTEQUAL "New password wont match!"
#define MX_FIELDS_NOTEMPTY "Fields cant be empty!"

#define MX_MSGHEIGHT(msg) (strlen(msg) + 20 * 10)
#define MX_MSGWIDTH(msg) (strlen(msg) * 4 > 400 ? 400 : strlen(msg) * 4)

#define MX_SEND_FILES_DIR "Client/files_send/"
#define MX_RECV_FILES_DIR "Client/files_recv/"

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

    this_uid_login,   // два єнама без запроса
    this_uid_logout,

    file_msg,
    failed_receiving_file,
} t_actions;
