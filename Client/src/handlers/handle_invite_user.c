#include "client.h"

void mx_handle_invite_user(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    int cid = cJSON_GetObjectItem(json, "cid")->valueint;
    int uid = cJSON_GetObjectItem(json, "uid")->valueint;
    char *login = cJSON_GetObjectItem(json, "login")->valuestring;
    t_chat_member *member = malloc(sizeof(t_chat_member));

    member->uid = uid;
    member->login = login;
    mx_push_back(mx_find_chat(info, cid)->users, member);
    free(member);
}
