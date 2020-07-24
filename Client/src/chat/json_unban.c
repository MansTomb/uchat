#include "client.h"

static void request(const t_chat *chat, int uid) {
    cJSON *jprof = cJSON_CreateObject();

    cJSON_AddNumberToObject(jprof, "json_type", make_unblock_user);
    cJSON_AddNumberToObject(jprof, "uid",  uid);
    cJSON_AddNumberToObject(jprof, "cid", chat->cid);

    mx_send_message_handler(jprof, chat->info->sock->sock);
    cJSON_Delete(jprof);
}

void mx_unban_user_wrapper(t_chat *chat, int uid) {
    request(chat, uid);
}
