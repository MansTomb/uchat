#include "client.h"

// TODO change the look of json in future
static void add_bld_json(const char *id, const char *log_to_srv, int s_sock) {
    cJSON *jlogin = cJSON_CreateObject();
    char *string = NULL;

    cJSON_AddNumberToObject(jlogin, "json_type", make_new_personal_chat);
    cJSON_AddStringToObject(jlogin, "client_id", id);
    cJSON_AddStringToObject(jlogin, "log_to_srv", log_to_srv);

    string = cJSON_Print(jlogin);
    if (!string || send(s_sock, string, strlen(string), 0) == -1)
        fprintf(stderr, "login: 'send' error occured\n");
    cJSON_Delete(jlogin);
    if (MX_MALLOC_SIZE(string))
        free(string);
}

void mx_add_contact_build_json_wrapper(t_contacts *contacts) {
    add_bld_json(mx_entry_get_text(contacts->dialog->entry),
                 mx_entry_get_text(contacts->dialog->entry),
                 contacts->info->sock->sock);
}
