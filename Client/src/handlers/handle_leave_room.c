#include "client.h"

static int find_user(t_chat *chat, int uid) {
    t_chat_member *member = NULL;

    if (chat) {
        for (size_t i = 0; i < chat->users->size; ++i) {
            member = mx_get_index(chat->users, i)->data;
            if (member->uid == uid)
                return i;
        }
    }
    return -1;
}

void mx_handle_leave_room(t_info *info, cJSON *json) {
    int cid = cJSON_GetObjectItem(json, "cid")->valueint;
    int uid = cJSON_GetObjectItem(json, "uid")->valueint;
    t_chat *chat = mx_find_chat(info, cid);
    int lid = find_user(chat, uid);

    if (lid > 0 && chat->info->cl_data->profile->id != uid)
        mx_pop_index(chat->users, lid);
    else if (chat->info->cl_data->profile->id == uid)
        mx_chat_destroy(info, cid);
}
