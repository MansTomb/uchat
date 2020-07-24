#include "client.h"

t_chat *mx_find_chat(t_info *info, int cid) {
    t_list *clist = info->chat_list;
    t_chat *chat = NULL;

    for (size_t i = 0; i < clist->size; ++i) {
        chat = mx_get_index(clist, i)->data;
        if (chat->cid == cid)
            return chat;
    }
    return NULL;
}

t_message *mx_find_message(t_chat *chat, int mid) {
    t_list *msglist = chat->msg_list;
    t_message *msg = NULL;

    for (size_t i = 0; i < msglist->size; ++i) {
        msg = mx_get_index(msglist, i)->data;
        if (msg->mid == mid)
            return msg;
    }
    return NULL;
}

t_chat_member *mx_find_cmember(t_chat *chat, char *name) {
    t_list *users = chat->users;
    t_chat_member *user = NULL;

    for (size_t i = 0; i < users->size; ++i) {
        user = mx_get_index(users, i)->data;
        if (strcmp(user->login, name) == 0)
            return user;
    }
    return NULL;
}

t_chat_member *mx_find_uid_private(t_chat *chat) {
    t_list *users = chat->users;
    t_chat_member *user = NULL;

    for (size_t i = 0; i < users->size; ++i) {
        user = mx_get_index(users, i)->data;
        if (user->uid != chat->info->cl_data->profile->id)
            return user;
    }
    return NULL;
}

t_contact *mx_find_contant(t_info *info, int uid) {
    t_list *contacts = info->cl_data->contacts;
    t_contact *node = NULL;

    if (contacts) {
        for (size_t i = 0; i < contacts->size; ++i) {
            node = mx_get_index(contacts, i)->data;
            if (node->cid == uid)
                return node;
        }
    }
    return NULL;
}
