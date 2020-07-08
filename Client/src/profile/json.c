#include "client.h"

static void upd_prof_bld_json(const t_info *info, const int *s_sock) {
    cJSON *jprof = cJSON_CreateObject();
    const t_profile *prof = info->windows->prof;

    cJSON_AddNumberToObject(jprof, "json_type", make_update_profile);
    cJSON_AddNumberToObject(jprof, "uid", info->cl_data->profile->id);
    cJSON_AddStringToObject(jprof, "fname", mx_entry_get_text(prof->fname));
    cJSON_AddStringToObject(jprof, "sname", mx_entry_get_text(prof->lname));
    cJSON_AddStringToObject(jprof, "email", mx_entry_get_text(prof->email));
    cJSON_AddStringToObject(jprof, "status", "");
    cJSON_AddNumberToObject(jprof, "snot", info->cl_data->profile->sound_noty);
    cJSON_AddNumberToObject(jprof, "vnot", info->cl_data->profile->vs_noty);
    cJSON_AddNumberToObject(jprof, "enot", info->cl_data->profile->email_noty);

    mx_send_message_handler(jprof, *s_sock);
    cJSON_Delete(jprof);
}

void upd_profile(t_info *info) {
    mx_save_login_data(info);
}

void mx_upd_prof_build_json_wrapper(t_info *info) {
    upd_prof_bld_json(info, &info->sock->sock);
    mx_wait_for_json(info, success_update_profile, success_update_profile);
    upd_profile(info);
}
