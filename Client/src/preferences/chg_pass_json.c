#include "client.h"

//     make_change_password,
//     failed_change_password,         // --
//     success_change_password,        // valid hash

// клиент
// { "json_type": 9, "login": "trohalska", "hash": "7", "new_hash": "444"}
// сервер
// {
// "json_type": 11
// }
// SQL error [change password]: query aborted
// {
// "json_type": 10
// }

static void send_request(const t_info *info) {
    cJSON *jobj = cJSON_CreateObject();
    char *hash_pass = mx_create_hash("12345");

    cJSON_AddNumberToObject(jobj, "json_type", make_change_password);
    cJSON_AddStringToObject(jobj, "login", info->cl_data->profile->login); // we need to send our client uid
    cJSON_AddStringToObject(jobj, "hash", ""); // old pass
    cJSON_AddStringToObject(jobj, "new_hash", "1"); // new pass

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

void mx_chg_pass_json(t_info *info, const char *old_pass, const char *new_pass) {
    send_request(info);
    mx_wait_for_json(info, success_change_password, failed_change_password);
}
