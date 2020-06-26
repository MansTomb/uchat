#include "client.h"

static void free_wrapper(char **str, cJSON **jmessage) {
    cJSON_Delete(*jmessage);
    if (MX_MALLOC_SIZE(*str))
        free(*str);
}

static void send_messege_json(const t_info *info, int s_sock) {
    cJSON *jmessage = cJSON_CreateObject();
    char *str = NULL;

    cJSON_AddNumberToObject(jmessage, "json_type", send_message);
    cJSON_AddNumberToObject(jmessage, "uid", info->cl_data->profile->id);
    cJSON_AddNumberToObject(jmessage, "chat_id", 1);
    cJSON_AddNumberToObject(jmessage, "type", 1);
    // cJSON_AddStringToObject(jmessage, "content", info->);

    str = cJSON_Print(jmessage);
    if (!str || send(s_sock, str, strlen(str), 0) == -1)
        fprintf(stderr, "login: 'send' error occured\n");
    free_wrapper(&str, &jmessage);
}

void mx_login_build_json_wrapper(t_info *info) {
    send_messege_json(mx_entry_get_text(), info->sock->sock);
}
