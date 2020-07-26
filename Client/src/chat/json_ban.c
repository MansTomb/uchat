#include "client.h"

static void del_user(t_chat *chat, int uid) {
    t_chat_member *member = NULL;

    for (size_t i = 0; i < chat->users->size; ++i) {
        member = mx_get_index(chat->users, i)->data;
        if (member->uid == uid) {
            mx_pop_index(chat->users, i);
            return;
        }
    }
}

static void request(const t_chat *chat, int uid) {
    cJSON *jprof = cJSON_CreateObject();

    cJSON_AddNumberToObject(jprof, "json_type", make_block_user);
    cJSON_AddNumberToObject(jprof, "uid",  uid);
    cJSON_AddNumberToObject(jprof, "cid", chat->cid);
    mx_send_message_handler(jprof, chat->info->sock->sock);
    cJSON_Delete(jprof);
}

void mx_ban_user_wrapper(t_chat *chat, int uid) {
    request(chat, uid);
    // del_user(chat, uid);
}
