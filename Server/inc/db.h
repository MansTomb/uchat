#pragma once
#include "server.h"

typedef enum {
    mx_make_register,
    mx_failed_register,
    mx_success_register,
    mx_make_authorization,
    mx_failed_authorization,
    mx_success_authorization,
    mx_make_deletion,
    mx_failed_deletion,
    mx_success_deletion,
    mx_make_change_password,
    mx_failed_change_password,
    mx_success_change_password,
    mx_make_update_profile,
    mx_success_update_profile,
    mx_get_client_data,
    mx_send_client_data,
    mx_get_client_contacts,
    mx_send_client_contacts,
    mx_get_client_chats,
    mx_send_client_chats,
    mx_get_client_messages,
    mx_send_client_messages,
    mx_make_new_chat,
    mx_send_message,
} t_actions;

int check(int rc, char *err, char *desc);

int mx_create_db(sqlite3 *db);
int mx_init_db(sqlite3 **db);
void mx_close_db(sqlite3 *db);

cJSON *mx_registration(sqlite3 *db, cJSON *reg);
