#include "client.h"

static void request(const t_invite_user *inv) {
    cJSON *jprof = cJSON_CreateObject();

    cJSON_AddNumberToObject(jprof, "json_type", make_add_user_in_chat);
    cJSON_AddStringToObject(jprof, "login", mx_entry_get_text(inv->entry));
    cJSON_AddNumberToObject(jprof, "cid", inv->chat->cid);

    mx_send_message_handler(jprof, inv->info->sock->sock);
    cJSON_Delete(jprof);
}

void mx_invite_json_wrapper(t_invite_user *inv) {
    request(inv);
}
