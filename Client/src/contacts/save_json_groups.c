#include "client.h"

t_group *get_grp(const cJSON *i) {
    t_group *g = malloc(sizeof(t_contact));

    g->id = cJSON_GetObjectItemCaseSensitive(i, "gid")->valueint;
    g->name = cJSON_GetObjectItemCaseSensitive(i, "gname")->valuestring;
    return g;
}

static void exist_grp(t_list *g_list, const t_info *info, const cJSON *i) {
    t_list_node *node = g_list ? g_list->head : NULL;
    int g_id = cJSON_GetObjectItemCaseSensitive(i, "gid")->valueint;
    bool exist = false;

    for (; node; node = node->next) {
        if (((t_group *)node->data)->id == g_id) {
            exist = true;
            break;
        }
    }
    if (!exist) {
        mx_push_back(info->cl_data->cont_grp_names, get_grp(i));
    }
}

void mx_upd_groups_list(const t_info *info) {
    if (cJSON_IsObject(info->json)) {
        cJSON *iterator = NULL;
        cJSON *groups = cJSON_GetObjectItem(info->json, "groups");

        if (cJSON_IsArray(groups)) {
            cJSON_ArrayForEach(iterator, groups) {
                exist_grp(info->cl_data->cont_grp_names, info, iterator);
            }
        }
        else
            fprintf(stderr, "user group json saving error\n");
    }
    else
        fprintf(stderr, "user group json saving error\n");
}
