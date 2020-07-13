#include "client.h"

static void send_contacts_request(const t_info *info) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", get_client_contacts);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id);

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

static void chk_add_exist_grp(char *g_name, t_list *g_list) {
    t_list_node *node = g_list ? g_list->head : NULL;
    bool exist = false;

    for (; node; node = node->next) {
        if (strcmp((char *)node->data, g_name) == 0) {
            exist = true;
            printf("Exist! -> %s\n", g_name);
            break;
        }
    }
    if (!exist) {
        printf("Not Exist! -> %s\n", g_name);
        mx_push_back(g_list, g_name);
    }
}

static t_contact *get_contact(const cJSON *iterator) {
    t_contact *c = malloc(sizeof(t_contact));

    c->cid = cJSON_GetObjectItemCaseSensitive(iterator, "coid")->valueint;
    c->login = cJSON_GetObjectItemCaseSensitive(iterator, "login")->valuestring;
    c->f_name = cJSON_GetObjectItemCaseSensitive(iterator, "fname")->valuestring;
    c->s_name = cJSON_GetObjectItemCaseSensitive(iterator, "sname")->valuestring;
    c->email = cJSON_GetObjectItemCaseSensitive(iterator, "email")->valuestring;
    c->stat = cJSON_GetObjectItemCaseSensitive(iterator, "status")->valuestring;
    // c->active = cJSON_GetObjectItemCaseSensitive(iterator, "active")->valuestring;
    c->grp_id = cJSON_GetObjectItemCaseSensitive(iterator, "gid")->valueint;
    c->grp_name = cJSON_GetObjectItemCaseSensitive(iterator, "gname")->valuestring;
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
                chk_add_exist_grp(((t_contact *)info->cl_data->contacts->tail->data)->grp_name, info->cl_data->cont_grp_names);
            }
        }
        else
            fprintf(stderr, "json saving error\n");
    }
    else
        fprintf(stderr, "json saving error\n");
}

void mx_get_json_contacts(t_info *info) {
    send_contacts_request(info);
    mx_wait_for_json(info, send_client_contacts, send_client_contacts);
    save_contacts(info);
}
