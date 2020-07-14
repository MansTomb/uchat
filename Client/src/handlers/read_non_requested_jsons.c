#include "client.h"

bool mx_handle_if_not_requested(t_info *info, cJSON *json) {
    switch (cJSON_GetObjectItem(json, "json_type")->valueint) {
        case send_message:
            mx_handle_send_message(info, json);
            return 0;
        case edit_message:
            mx_handle_edit_message(info, json);
            return 0;
        case delete_message:
            mx_handle_delete_message(info, json);
            return 0;
    }
    cJSON_Delete(json);
    return 1;
}
