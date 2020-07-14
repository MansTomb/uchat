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

static void build_json2(const t_chat *chat, char *content, const int *s_sock) {
    cJSON *jprof = cJSON_CreateObject();

    cJSON_AddNumberToObject(jprof, "json_type", file_msg);
    cJSON_AddNumberToObject(jprof, "uid", chat->info->cl_data->profile->id);
    cJSON_AddNumberToObject(jprof, "cid", chat->cid);
    cJSON_AddNumberToObject(jprof, "type", 2);
    cJSON_AddStringToObject(jprof, "content", content);

    mx_send_message_handler(jprof, *s_sock);
    cJSON_Delete(jprof);
}

void mx_send_message_t2_json_wrapper(t_chat *chat, char *content) {
    build_json2(chat, content, &chat->info->sock->sock);
}
