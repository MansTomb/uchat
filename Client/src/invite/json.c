#include "client.h"

static void request(const t_invite_user *inv) {
    cJSON *jprof = cJSON_CreateObject();

    cJSON_AddNumberToObject(jprof, "json_type", edit_message);
    cJSON_AddStringToObject(jprof, "login", mx_entry_get_text(inv->entry));
    cJSON_AddNumberToObject(jprof, "cid", inv->chat->cid);

    mx_send_message_handler(jprof, inv->info->sock->sock);
    cJSON_Delete(jprof);
}

void mx_invite_json_wrapper(t_invite_user *inv) {
    request(inv);
    // mx_wait_for_json(info, success_authorization, failed_authorization);
    // if (mx_get_jtype(inv->info, succs))
    // else if (mx_get_jtype(inv->info, fail))
}
