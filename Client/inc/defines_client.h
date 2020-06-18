#pragma once

#include "uchat.h"

/*    Defines for widgets placement */
#define WIDTH 1280
#define HEIGHT 720

/*    Define for укорачивания(не нашёл англ слова в голове) */
#define MX_BOX_V GTK_ORIENTATION_VERTICAL
#define MX_CB G_CALLBACK
#define MX_GSIG_CON g_signal_connect

/* Types for sending jsons */
typedef enum {
    make_register,
    failed_register,
    success_register,
    make_authorization,
    failed_authorization,
    success_authorization,
    make_deletion,
    failed_deletion,
    success_deletion,
    make_change_password,
    failed_change_password,
    success_change_password,
    make_update_profile,
    success_update_profile,
    get_client_data,
    send_client_data,
    get_client_contacts,
    send_client_contacts,
    get_client_chats,
    send_client_chats,
    get_client_messages,
    send_client_messages,
    make_new_chat,
    send_message,
} t_actions;
