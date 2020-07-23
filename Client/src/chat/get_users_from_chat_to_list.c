#include "client.h"

static t_chat_member *get_user(const cJSON *iterator) {
    t_chat_member *c = malloc(sizeof(t_chat_member));

    c->uid = cJSON_GetObjectItemCaseSensitive(iterator, "uid")->valueint;
    c->login = cJSON_GetObjectItemCaseSensitive(iterator, "login")->valuestring;
    return c;
}

void mx_save_chat_users(t_chat *chat, const cJSON *users) {
    cJSON *iterator = NULL;

    if (cJSON_IsArray(users)) {
        cJSON_ArrayForEach(iterator, users) {
            mx_push_back(chat->users, get_user(iterator));
        }
    }
    else
        fprintf(stderr, "user from chat saving error\n");
}
