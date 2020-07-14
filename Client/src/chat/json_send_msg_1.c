#include "client.h"

static void build_json(const t_chat *chat, char *content, const int *s_sock) {
    cJSON *jprof = cJSON_CreateObject();

    cJSON_AddNumberToObject(jprof, "json_type", send_message);
    cJSON_AddNumberToObject(jprof, "uid", chat->info->cl_data->profile->id);
    cJSON_AddNumberToObject(jprof, "cid", chat->cid);
    cJSON_AddNumberToObject(jprof, "type", 1);
    cJSON_AddStringToObject(jprof, "content", content);

    mx_send_message_handler(jprof, *s_sock);
    cJSON_Delete(jprof);
}

void mx_send_message_t1_json_wrapper(t_chat *chat, char *content) {
    build_json(chat, content, &chat->info->sock->sock);
}
