#pragma once

#include "uchat.h"

/*    Defines for widgets placement */
#define WIDTH 1280
#define HEIGHT 720

/*    Define for укорачивания(не нашёл англ слова в голове) */
#define MX_BOX_V GTK_ORIENTATION_VERTICAL
#define MX_CB G_CALLBACK
#define MX_GSIG_CON g_signal_connect

#define MX_PASS_NONPRINT "Password contain non printable characters!"
#define MX_NEWPASS_NOTEQUAL "New password wont match!"
#define MX_FIELDS_NOTEMPTY "Fields cant be empty!"

/* Types for sending jsons */
typedef enum {
    make_register,
    failed_register,                // when login exists in db
    success_register,               // --

    make_authorization,
    failed_authorization,           // --
    success_authorization,          // when login exists in db in 1 example, and login and hash valid

    make_deletion,                      // зробити
    failed_deletion,
    success_deletion,

    make_change_password,
    failed_change_password,         // --
    success_change_password,        // when login exists in db in 1 example, and login and hash valid

    make_update_profile,
    success_update_profile,

    get_client_data,                      // зробити
    send_client_data,

    get_client_contacts,
    send_client_contacts,

    get_client_chats,                      // зробити
    send_client_chats,

    get_client_messages,                      // зробити
    send_client_messages,

    make_add_new_contact,
    failed_add_new_contact,         // when contact doesn't exist in users
    success_add_new_contact,

    make_del_contact,
    failed_del_contact,             // when contact doesn't exist in contacts_list
    success_del_contact,

    make_new_personal_chat,
    failed_new_personal_chat,
    success_new_personal_chat,

    make_new_group_chat,                      // зробити
    get_new_group_chat,

    make_new_chanel,                      // зробити
    get_new_chanel,

    send_message,
    failed_send_message,                    // error db

    logout,
} t_actions;
