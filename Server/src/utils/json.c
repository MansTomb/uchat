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

cJSON *mx_su_msg(cJSON *bd, char *s) {
    cJSON *json = cJSON_CreateObject();
    char *str;

    str = mx_strjoin_free(strdup(MX_VSTR(bd, "login")), s);
    cJSON_AddNumberToObject(json, "json_type", send_message);
    cJSON_AddNumberToObject(json, "uid", 1);
    cJSON_AddNumberToObject(json, "cid", MX_VINT(bd, "cid"));
    cJSON_AddNumberToObject(json, "type", 1);
    cJSON_AddNumberToObject(json, "role", 2);
    cJSON_AddStringToObject(json, "content", str);
    mx_strdel(&str);
    return json;
}

cJSON *mx_bot_msg(cJSON *bd, char *s) {
    cJSON *json = cJSON_CreateObject();

    cJSON_AddNumberToObject(json, "json_type", send_message);
    cJSON_AddNumberToObject(json, "uid", 1);
    cJSON_AddNumberToObject(json, "cid", MX_VINT(bd, "cid"));
    cJSON_AddNumberToObject(json, "type", 1);
    cJSON_AddNumberToObject(json, "role", 2);
    cJSON_AddStringToObject(json, "content", s);
    return json;
}
