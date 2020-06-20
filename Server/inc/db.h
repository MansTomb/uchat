#pragma once
#include "server.h"

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

    make_new_personal_chat,
    failed_new_personal_chat,
    success_new_personal_chat,

    make_new_group_chat,
    get_new_group_chat,

    make_new_chanel,
    get_new_chanel,

    send_message,
} t_actions;

int mx_check(int rc, char *err, char *desc);

int mx_create_db(sqlite3 *db);
int mx_init_db(sqlite3 **db);
void mx_close_db(sqlite3 *db);

cJSON *mx_registration(sqlite3 *db, cJSON *jsn);
cJSON *mx_authorization(sqlite3 *db, cJSON *jsn);

cJSON *mx_create_personal_chat(sqlite3 *db, cJSON *jsn);
void mx_get_present_chat(sqlite3 *db, cJSON *jsn);
