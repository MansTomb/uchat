#include "client.h"

static void free_wrapper(char **str, cJSON **jobj) {
    cJSON_Delete(*jobj);
    if (MX_MALLOC_SIZE(str))
        free(*str);
    if (MX_MALLOC_SIZE(hash_pass))
        free(*hash_pass);
}

static void send_contacts_request(t_info *info) {
    cJSON *jobj = cJSON_CreateObject();
    char *str = NULL;

    cJSON_AddNumberToObject(jobj, "json_type", get_client_contacts);
    cJSON_AddNumberToObject(jobj, "uid", info->client->uid); // we need to send our client uid

    str = cJSON_Print(jobj);
    if (!str || send(info->sock->sock, str, strlen(str), 0) == -1)
        fprintf(stderr, "get client contacts: 'send' error occured\n");
    free_wrapper(&str, &jobj);
}

// TODO save_contacts (parse array from json and asve it into list)
void save_contacts(t_info *info) {
    for (int i = 0; i < cJSON_GetArraySize(cJSON_GetObjectItem(info->json, "contacts")); ++i) {
        cJSON *contacts = cJSON_GetArrayItem(cJSON_GetObjectItem(info->json, "contacts"), i);
        int cid = cJSON_GetObjectItem(contacts, "contact_id")->valueint;
        // это все надо в лист/структурку
        char *login = cJSON_GetObjectItem(contacts, "login")->valuestring;
        char *first_name = cJSON_GetObjectItem(contacts, "first_name")->valuestring;
        char *second_name = cJSON_GetObjectItem(contacts, "second_name")->valuestring;
        char *email = cJSON_GetObjectItem(contacts, "email")->valuestring;
        char *status = cJSON_GetObjectItem(contacts, "status")->valuestring;
        char *group_id = cJSON_GetObjectItem(contacts, "group_id")->valueint;
        char *group_name = cJSON_GetObjectItem(contacts, "group_name")->valuestring;

        // cJSON_ArrayForEach(); надо чекнуть как работает этот макрос
        // free(contacts); может надо а может и не надо
    }
}

void mx_get_json_contact(t_info *info) {
    send_contacts_request(info);
    mx_wait_for_json(info, send_client_contacts, send_client_contacts);
    save_contacts(info);
}
