#include "client.h"

static void send_contacts_request(t_info *info) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", get_client_contacts);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id); // we need to send our client uid

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

// надо разбить на 2 функи
static void save_contacts(t_info *info) {
    if (cJSON_IsObject(info->json)) {
        cJSON *iterator = NULL;
        cJSON *contacts = cJSON_GetObjectItem(info->json, "contacts");

        cJSON_ArrayForEach(iterator, contacts) {
            t_contact *c = malloc(sizeof(t_contact));

            c->cid = cJSON_GetObjectItemCaseSensitive(iterator, "coid")->valueint;
            // c->login = cJSON_GetObjectItemCaseSensitive(iterator, "login")->valuestring;
            // c->f_name = cJSON_GetObjectItemCaseSensitive(iterator, "fname")->valuestring;
            // c->s_name = cJSON_GetObjectItemCaseSensitive(iterator, "sname")->valuestring;
            // c->email = cJSON_GetObjectItemCaseSensitive(iterator, "email")->valuestring;
            // c->stat = cJSON_GetObjectItemCaseSensitive(iterator, "status")->valuestring;
            // c->active = cJSON_GetObjectItemCaseSensitive(iterator, "active")->valuestring;
            // c->grp_id = cJSON_GetObjectItemCaseSensitive(iterator, "gid")->valueint;
            // c->grp_name = cJSON_GetObjectItemCaseSensitive(iterator, "gname")->valuestring;
            mx_push_back(info->cl_data->contacts, c);
        }
        // cJSON_Delete(info->json);
    }
    else
        fprintf(stderr, "json saving error\n");
}

void mx_get_json_contact(t_info *info) {
    send_contacts_request(info);
    mx_wait_for_json(info, send_client_contacts, send_client_contacts);
    save_contacts(info);
}
