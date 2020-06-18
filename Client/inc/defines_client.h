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
#define MX_MAKE_REGISTER 0
#define MX_MAKE_AUTORIZATION 3
#define MX_MAKE_DELETION 6
#define MX_MAKE_CHANGE_PASSWORD 9
#define MX_MAKE_UPDATE_PROFILE 12
#define MX_GET_CLIENT_DATA 14
#define MX_GET_CLIENT_CONTACTS 16
#define MX_GET_CLIENT_CHATS 18
#define MX_GET_CLIENT_MESSAGES 20
#define MX_MAKE_NEW_CHAT 22
