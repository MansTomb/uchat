#include "client.h"

static void request(t_info *info, char *content, const int *s_sock) {
    cJSON *jprof = cJSON_CreateObject();

    cJSON_AddNumberToObject(jprof, "json_type", superuser_message);
    cJSON_AddStringToObject(jprof, "content", content);

    mx_send_message_handler(jprof, *s_sock);
    cJSON_Delete(jprof);
}

void mx_admin_send_wrapper(t_info *info, char *content) {
    request(info, content, &info->sock->sock);
}
