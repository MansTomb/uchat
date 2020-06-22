#include "client.h"

bool mx_get_jtype(t_info *info, int type) {
    return cJSON_GetObjectItem(info->json, "json_type")->valueint == type;
}
