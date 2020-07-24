#pragma once
#include "server.h"

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

typedef enum {
    one_msg,
    big_msg,
    big_msg_end,
    file,
    file_end
} t_datatype;

typedef struct {
    sqlite3 *db;
    cJSON *jsn;
} t_sql;

int mx_check(int rc, char *err, char *desc);

int mx_create_db(sqlite3 *db);
int mx_init_db(sqlite3 **db);
void mx_close_db(sqlite3 *db);

cJSON *mx_registration(sqlite3 *db, cJSON *jsn);
cJSON *mx_authorization(sqlite3 *db, cJSON *jsn);
cJSON *mx_change_password(sqlite3 *db, cJSON *jsn);
cJSON *mx_update_profile(sqlite3 *db, cJSON *jsn);

cJSON *mx_send_message(sqlite3 *db, cJSON *jsn);
void mx_insert_message_in_db(sqlite3 *db, cJSON *jsn);
cJSON *mx_edit_message(sqlite3 *db, cJSON *jsn);
cJSON *mx_if_message_on_mail(sqlite3 *db, cJSON *jsn);
cJSON *mx_superuser_message(sqlite3 *db, cJSON *jsn);

void mx_get_all_users_in_chat(sqlite3 *db, cJSON *jsn, int cid);

cJSON *mx_file_manage(sqlite3 *db, cJSON *jsn);

cJSON *mx_add_new_contact(sqlite3 *db, cJSON *jsn);
cJSON *mx_del_contact(sqlite3 *db, cJSON *jsn);

cJSON *mx_create_personal_chat(sqlite3 *db, cJSON *jsn);
void mx_get_present_chat(sqlite3 *db, cJSON *jsn);
cJSON *mx_create_group_chat_channel(sqlite3 *db, cJSON *jsn);
cJSON *mx_create_contact_group(sqlite3 *db, cJSON *jsn);
cJSON *mx_del_contact_group(sqlite3 *db, cJSON *jsn);

cJSON *mx_get_contact_list(sqlite3 *db, cJSON *jsn);
cJSON *mx_get_clients_chats(sqlite3 *db, cJSON *jsn);
cJSON *mx_get_client_chat_messages(sqlite3 *db, cJSON *jsn);

cJSON *mx_search_user(sqlite3 *db, cJSON *jsn);
cJSON *mx_delete_user(sqlite3 *db, cJSON *jsn);

cJSON *mx_invite(sqlite3 *db, cJSON *jsn);
cJSON *mx_get_chat_for_invite(sqlite3 *db, cJSON *jsn);

cJSON *mx_leave_chat(sqlite3 *db, cJSON *jsn);
