#include "client.h"

static void send_contacts_request(t_info *info) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", get_client_contacts);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id); // we need to send our client uid

    mx_send_message_handler(jobj, info->sock->sock);
    cJSON_Delete(jobj);
}

t_contact *mx_contact_constructor(cJSON **jc) {
    t_contact *c = (t_contact *)malloc(sizeof(t_contact));

    c->cid = cJSON_GetObjectItem(*jc, "coid")->valueint;
    c->login = cJSON_GetObjectItem(*jc, "login")->valuestring;
    c->f_name = cJSON_GetObjectItem(*jc, "fname")->valuestring;
    c->s_name = cJSON_GetObjectItem(*jc, "sname")->valuestring;
    c->email = cJSON_GetObjectItem(*jc, "email")->valuestring;
    c->stat = cJSON_GetObjectItem(*jc, "status")->valuestring;
    c->grp_id = cJSON_GetObjectItem(*jc, "gid")->valueint;
    c->grp_name = cJSON_GetObjectItem(*jc, "gname")->valuestring;
    return c;
}

void save_contacts(t_info *info) {
    for (int i = 0; i < cJSON_GetArraySize(cJSON_GetObjectItem(info->json, "contacts")); ++i) {
        cJSON *contacts = cJSON_GetArrayItem(cJSON_GetObjectItem(info->json, "contacts"), i);
        mx_push_back(info->cl_data->contacts, mx_contact_constructor(&contacts));
        free(contacts); // может надо а может и не надо
    }
}

void mx_get_json_contact(t_info *info) {
    send_contacts_request(info);
    mx_wait_for_json(info, send_client_contacts, send_client_contacts);
    save_contacts(info);
}
