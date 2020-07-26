#include "client.h"

static void request(const t_message_img *msg, const int *s_sock) {
    cJSON *jprof = cJSON_CreateObject();

    cJSON_AddNumberToObject(jprof, "json_type", delete_message);
    cJSON_AddNumberToObject(jprof, "uid", msg->info->cl_data->profile->id);
    cJSON_AddNumberToObject(jprof, "cid", msg->cid);
    cJSON_AddNumberToObject(jprof, "mid", msg->mid);
    mx_send_message_handler(jprof, *s_sock);
    cJSON_Delete(jprof);
}

void mx_delete_message_t2_json_wrapper(t_message_img *msg) {
    request(msg, &msg->info->sock->sock);
}
