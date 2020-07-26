#include "client.h"

t_group *get_grp(const cJSON *i) {
    t_group *g = malloc(sizeof(t_contact));

    g->id = cJSON_GetObjectItemCaseSensitive(i, "gid")->valueint;
    g->name = cJSON_GetObjectItemCaseSensitive(i, "gname")->valuestring;
    return g;
}

void mx_upd_groups_list(const t_info *info) {
    if (cJSON_IsObject(info->json)) {
        cJSON *iterator = NULL;
        cJSON *groups = cJSON_GetObjectItem(info->json, "groups");

        if (MX_MALLOC_SIZE(info->cl_data->cont_grp_names) > 0) {
            mx_clr_custom_lst(info->cl_data->cont_grp_names);
        }
        info->cl_data->cont_grp_names = mx_create_list();
        if (cJSON_IsArray(groups)) {
            cJSON_ArrayForEach(iterator, groups) {
                mx_push_back(info->cl_data->cont_grp_names, get_grp(iterator));
            }
        }
        else
            fprintf(stderr, "user group json saving error\n");
    }
    else
        fprintf(stderr, "user group json saving error\n");
}
