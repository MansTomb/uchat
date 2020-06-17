#pragma once

/*    Defines for widgets placement */
#define WIDTH 1280
#define HEIGHT 720

/* Login screen widgets placements */
#define L_LOGBT_W (WIDTH / 2)
#define L_LOGBT_H (HEIGHT / 2)
#define L_REGBT_W (WIDTH / 2 - 100)
#define L_REGBT_H (HEIGHT / 2)
#define L_USRLB_W (WIDTH / 2 - 100) 
#define L_USRLB_H (HEIGHT / 2 - 115)
#define L_USRENT_W (WIDTH / 2 - 100)
#define L_USRENT_H (HEIGHT / 2 - 100)
#define L_PASLB_W (WIDTH / 2 - 100)
#define L_PASLB_H (HEIGHT / 2 - 65)
#define L_PASENT_W (WIDTH / 2 - 100)
#define L_PASENT_H (HEIGHT / 2 - 50)

/* Register screen widgets placements */

#define R_BACKBT_W (WIDTH / 2 - 125)
#define R_BACKBT_H (HEIGHT / 2 + 50)
#define R_REGBT_W (WIDTH / 2)
#define R_REGBT_H (HEIGHT / 2 + 50)
#define R_USRLB_W (WIDTH / 2 - 100) 
#define R_USRLB_H (HEIGHT / 2 - 115)
#define R_USRENT_W (WIDTH / 2 - 100)
#define R_USRENT_H (HEIGHT / 2 - 100)
#define R_PASLB_W (WIDTH / 2 - 100)
#define R_PASLB_H (HEIGHT / 2 - 65)
#define R_PASENT_W (WIDTH / 2 - 100)
#define R_PASENT_H (HEIGHT / 2 - 50)
#define R_PAS2LB_W (WIDTH / 2 - 100)
#define R_PAS2LB_H (HEIGHT / 2 - 15)
#define R_PAS2ENT_W (WIDTH / 2 - 100)
#define R_PAS2ENT_H (HEIGHT / 2)

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
