#include "client.h"

static void free_wrapper(char **str, cJSON **jobj) {
    cJSON_Delete(*jobj);
    if (MX_MALLOC_SIZE(str))
        free(*str);
}

static void send_contacts_request(t_info *info) {
    cJSON *jobj = cJSON_CreateObject();
    char *str = NULL;

    cJSON_AddNumberToObject(jobj, "json_type", get_client_contacts);
    cJSON_AddNumberToObject(jobj, "uid", info->cl_data->profile->id); // we need to send our client uid

    str = cJSON_Print(jobj);
    if (!str || send(info->sock->sock, str, strlen(str), 0) == -1)
        fprintf(stderr, "get client contacts: 'send' error occured\n");
    free_wrapper(&str, &jobj);
}

t_contact *mx_contact_constructor(cJSON **jc) {
    t_contact *c = (t_contact *)malloc(sizeof(t_contact));

    c->cid = cJSON_GetObjectItem(*jc, "contact_id")->valueint;
    c->login = cJSON_GetObjectItem(*jc, "login")->valuestring;
    c->f_name = cJSON_GetObjectItem(*jc, "first_name")->valuestring;
    c->s_name = cJSON_GetObjectItem(*jc, "second_name")->valuestring;
    c->email = cJSON_GetObjectItem(*jc, "email")->valuestring;
    c->stat = cJSON_GetObjectItem(*jc, "status")->valuestring;
    c->grp_id = cJSON_GetObjectItem(*jc, "group_id")->valueint;
    c->grp_name = cJSON_GetObjectItem(*jc, "group_name")->valuestring;
    return c;
}

// TODO save_contacts (parse array from json and asve it into list)
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

static void add_bld_json(const char *id, const char *log_to_srv, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();
    char *str = NULL;

    cJSON_AddNumberToObject(jlogin, "json_type", make_add_new_contact);
    cJSON_AddStringToObject(jlogin, "client_id", id);
    cJSON_AddStringToObject(jlogin, "log_to_srv", log_to_srv);

    str = cJSON_Print(jlogin);
    if (!str || send(s_sock, str, strlen(str), 0) == -1)
        fprintf(stderr, "make add new contact: 'send' error occured\n");
    cJSON_Delete(jlogin);
    if (MX_MALLOC_SIZE(str))
        free(str);
}

void mx_add_contact_build_json_wrapper(t_contacts *contacts) {
    add_bld_json(mx_entry_get_text(contacts->dialog->entry),
                 mx_entry_get_text(contacts->dialog->entry),
                 contacts->info->sock->sock);
}
