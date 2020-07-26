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

static int wrap(void *data) {
    t_left_room *lr = data;

    mx_chat_destroy(lr->info, lr->cid);
    return 0;
}

void mx_handle_leave_room(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    t_left_room *lr = malloc(sizeof(t_left_room));
    t_chat *chat = NULL;
    int uid = cJSON_GetObjectItem(json, "uid")->valueint;
    int lid = 0;

    lr->cid = cJSON_GetObjectItem(json, "cid")->valueint;
    lr->info = info;
    chat = mx_find_chat(info, lr->cid);
    if (chat) {
        lid = find_user(chat, uid);
        if (lid > 0 && chat->info->cl_data->profile->id != uid)
            mx_pop_index(chat->users, lid);
        else if (chat->info->cl_data->profile->id == uid)
            gdk_threads_add_idle(wrap, lr);
    }
}
