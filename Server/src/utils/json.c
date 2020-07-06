#include "server.h"

void mx_json_to_sending_buffer(char *buff, cJSON *json) {
    char *root;

    root = cJSON_Print(json);
    sprintf(buff, "%s", root);
}

int mx_check_err_json(cJSON *new) {
    const char *error_ptr;

    if (new == NULL)
        if ((error_ptr = cJSON_GetErrorPtr()) != NULL) {
            fprintf(stderr, "cJSON_Parse error, before: %s", error_ptr);
            return 1;
        }
    return 0;
}

cJSON *mx_this_uid_login_or_logout(int uid, int type) {
    cJSON *json = cJSON_CreateObject();

    cJSON_AddNumberToObject(json, "json_type", type);
    cJSON_AddNumberToObject(json, "uid", uid);
    return json;
}
