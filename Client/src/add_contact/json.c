#include "client.h"

// static void add_bld_json(const char *id, const char *log_to_srv, int s_sock) {
//     cJSON *jlogin = cJSON_CreateObject();

//     cJSON_AddNumberToObject(jlogin, "json_type", make_add_new_contact);
//     cJSON_AddStringToObject(jlogin, "client_id", id);
//     cJSON_AddStringToObject(jlogin, "log_to_srv", log_to_srv);

//     mx_send_message_handler(jlogin, s_sock);
//     cJSON_Delete(jlogin);
// }

// void mx_add_contact_build_json_wrapper(t_contacts *contacts) {
//     add_bld_json(mx_entry_get_text(contacts->dialog->entry),
//                  mx_entry_get_text(contacts->dialog->entry),
//                  contacts->info->sock->sock);
// }
