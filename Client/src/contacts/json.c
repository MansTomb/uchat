#include "client.h"

static void send_contacts_request(const t_info *info) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", get_client_contacts);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id);

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

static t_contact *get_contact(const cJSON *iterator) {
    t_contact *c = malloc(sizeof(t_contact));

    c->cid = cJSON_GetObjectItemCaseSensitive(iterator, "coid")->valueint;
    c->login = cJSON_GetObjectItemCaseSensitive(iterator, "login")->valuestring;
    c->f_name = cJSON_GetObjectItemCaseSensitive(iterator, "fname")->valuestring;
    c->s_name = cJSON_GetObjectItemCaseSensitive(iterator, "sname")->valuestring;
    c->email = cJSON_GetObjectItemCaseSensitive(iterator, "email")->valuestring;
    c->stat = cJSON_GetObjectItemCaseSensitive(iterator, "status")->valuestring;
    c->active = cJSON_GetObjectItemCaseSensitive(iterator, "active")->valueint;
    c->grp_id = cJSON_GetObjectItemCaseSensitive(iterator, "gid")->valueint;
    return c;
}

static void exist_cntct(t_list *c_list, const t_info *info, const cJSON *i) {
    t_list_node *node = c_list ? c_list->head : NULL;
    char *c_login = cJSON_GetObjectItemCaseSensitive(i, "login")->valuestring;
    bool exist = false;

    for (; node; node = node->next) {
        if (strcmp(((t_contact *)node->data)->login, c_login) == 0) {
            exist = true;
            break;
        }
    }
    if (!exist) {
        mx_push_back(info->cl_data->contacts, get_contact(i));
    }
}

static void save_contacts(const t_info *info) {
    if (cJSON_IsObject(info->json)) {
        cJSON *iterator = NULL;
        cJSON *contacts = cJSON_GetObjectItem(info->json, "contacts");

        if (cJSON_IsArray(contacts)) {
            cJSON_ArrayForEach(iterator, contacts) {
                exist_cntct(info->cl_data->contacts, info, iterator);
            }
        }
        else
            fprintf(stderr, "user contact json saving error\n");
    }
    else
        fprintf(stderr, "user contact json saving error\n");
}

void mx_get_json_contacts(t_info *info) {
    send_contacts_request(info);
    mx_wait_for_json(info, success_client_contacts, failed_client_contacts);
    if (mx_get_jtype(info, success_client_contacts)) {
        save_contacts(info);
        mx_upd_groups_list(info);
    }
}
