#include "client.h"

void mx_handle_being_invited(t_info *info, cJSON *json) { 
    if (!info->windows->ms)
        return;
    mx_chat_put(info, json);
}