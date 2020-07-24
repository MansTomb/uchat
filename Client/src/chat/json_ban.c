#include "client.h"

static void request(const t_chat *chat) {
    cJSON *jprof = cJSON_CreateObject();

    cJSON_AddNumberToObject(jprof, "json_type", make_leave_chat);
    cJSON_AddNumberToObject(jprof, "uid", chat->info->cl_data->profile->id);
    cJSON_AddNumberToObject(jprof, "cid", chat->cid);

    mx_send_message_handler(jprof, chat->info->sock->sock);
    cJSON_Delete(jprof);
}

void mx_ban_user_wrapper(t_chat *chat) {
    request(chat);
}
