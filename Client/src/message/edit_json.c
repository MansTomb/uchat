#include "client.h"

static void request(const t_message *msg, char *content, const int *s_sock) {
    cJSON *jprof = cJSON_CreateObject();

    cJSON_AddNumberToObject(jprof, "json_type", edit_message);
    cJSON_AddNumberToObject(jprof, "uid", msg->info->cl_data->profile->id);
    cJSON_AddNumberToObject(jprof, "cid", msg->cid);
    cJSON_AddNumberToObject(jprof, "mid", msg->mid);
    cJSON_AddStringToObject(jprof, "content", content);

    mx_send_message_handler(jprof, *s_sock);
    cJSON_Delete(jprof);
}

void mx_edit_message_t1_json_wrapper(t_message *msg, char *content) {
    request(msg, content, &msg->info->sock->sock);
}
