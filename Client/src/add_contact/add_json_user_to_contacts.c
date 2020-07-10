#include "client.h"

static void add_cnt_bld_json(const char *gname, const int coid, const int uid, int s_sock) {
    cJSON *jobj = cJSON_CreateObject();

    cJSON_AddNumberToObject(jobj, "json_type", make_add_new_contact);
    cJSON_AddNumberToObject(jobj, "uid", uid);
    cJSON_AddNumberToObject(jobj, "coid", coid);
    cJSON_AddStringToObject(jobj, "gname", gname);

    mx_send_message_handler(jobj, s_sock);
    cJSON_Delete(jobj);
}

static int get_uid(const t_list *list, const char *u_l, const char *c_l) {
    t_list_node *node = list ? list->head : NULL;

    for (; node; node = node->next) {
        if (strcmp(((t_user *)node->data)->login, u_l) == 0
            || strcmp(((t_user *)node->data)->login, c_l) == 0) {
            return ((t_user *)node->data)->id;
        }
    }
    return -1;
}

void mx_add_cnt_json_wrapper(t_contact_add *ac) {
    const char *usr_login = gtk_entry_get_text(GTK_ENTRY(ac->entry));
    char *gname = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ac->combobox));
    int coid = get_uid(ac->info->cl_data->tmp_users, usr_login, ac->info->cl_data->profile->login);

    if (coid != -1) {
        add_cnt_bld_json(gname, coid, ac->info->cl_data->profile->id, ac->info->sock->sock);
        mx_wait_for_json(ac->info, failed_add_new_contact, success_add_new_contact);
        mx_get_json_contacts(ac->info);
    }
    else {
        mx_dialog_warning_create(NULL, "The contact does not exist or this is your login.!\n");
    }
    mx_strdel(&gname);
}
