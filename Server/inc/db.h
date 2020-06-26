#pragma once
#include "server.h"

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

    get_client_data,                      // це профіль? якщо так то уже не треба
    send_client_data,

    get_client_contacts,
    send_client_contacts,

    get_client_chats,
    send_client_chats,

    get_client_chat_messages,
    send_client_chat_messages,

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

    edit_message,
    delete_message,
    success_edit_message,
    success_delete_message,
    failed_edit_delete_message,                    // error db

    logout,
} t_actions;

int mx_check(int rc, char *err, char *desc);

int mx_create_db(sqlite3 *db);
int mx_init_db(sqlite3 **db);
void mx_close_db(sqlite3 *db);

cJSON *mx_registration(sqlite3 *db, cJSON *jsn);
cJSON *mx_authorization(sqlite3 *db, cJSON *jsn);
cJSON *mx_change_password(sqlite3 *db, cJSON *jsn);
cJSON *mx_update_profile(sqlite3 *db, cJSON *jsn);

cJSON *mx_send_message(sqlite3 *db, cJSON *jsn);
cJSON *mx_edit_message(sqlite3 *db, cJSON *jsn);
cJSON *mx_if_message_on_mail(sqlite3 *db, cJSON *jsn);

cJSON *mx_add_new_contact(sqlite3 *db, cJSON *jsn);
cJSON *mx_del_contact(sqlite3 *db, cJSON *jsn);

cJSON *mx_create_personal_chat(sqlite3 *db, cJSON *jsn);
void mx_get_present_chat(sqlite3 *db, cJSON *jsn);

cJSON *mx_get_contact_list(sqlite3 *db, cJSON *jsn);
cJSON *mx_get_clients_chats(sqlite3 *db, cJSON *jsn);
cJSON *mx_get_client_chat_messages(sqlite3 *db, cJSON *jsn);
