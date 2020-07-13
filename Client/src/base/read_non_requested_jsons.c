#include "client.h"

static void text_message(t_info *info, cJSON *json) {
    t_message *msg = mx_message_build(info, json);

    mx_message_put(info, msg, cJSON_GetObjectItem(json, "cid")->valueint);
    cJSON_Delete(json);
}

static void handlse_send_message(t_info *info, cJSON *json) {
    switch (cJSON_GetObjectItem(json, "type")->valueint) {
        case 1:
            text_message(info, json);
    }
}

bool mx_handle_if_not_requested(t_info *info, cJSON *json) {
    switch (cJSON_GetObjectItem(json, "json_type")->valueint) {
        case send_message:
            handlse_send_message(info, json);
            return 0;
    }
    cJSON_Delete(json);
    return 1;
}
