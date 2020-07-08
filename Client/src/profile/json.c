#include "client.h"

static void upd_prof_bld_json(const t_info *info, int *s_sock) {
    cJSON *jprof = cJSON_CreateObject();
    // const t_profile *new_prof = info->windows->profile;
    char *str = NULL;

    cJSON_AddNumberToObject(jprof, "json_type", make_update_profile);
    cJSON_AddNumberToObject(jprof, "uid", info->cl_data->profile->id);
    cJSON_AddStringToObject(jprof, "fname", "");
    cJSON_AddStringToObject(jprof, "sname", "");
    cJSON_AddStringToObject(jprof, "email", "");
    cJSON_AddStringToObject(jprof, "status", "");
    cJSON_AddNumberToObject(jprof, "snot", 0);
    cJSON_AddNumberToObject(jprof, "vnot", 0);
    cJSON_AddNumberToObject(jprof, "enot", 0);

    str = cJSON_Print(jprof);
    if (!str || send(*s_sock, str, strlen(str), 0) == -1)
        fprintf(stderr, "make update profile: 'send' error occured\n");
    cJSON_Delete(jprof);
    if (MX_MALLOC_SIZE(str))
        free(str);
}

// void upd_profile(t_info *info) {
//     t_profile_data *prof = info->cl_data->profile;
//     char *p_id = mx_lltoa(prof->id);

//     mx_save_login_data(info);
//     gtk_entry_set_text(GTK_ENTRY(info->windows->profile->name), p_id);
//     gtk_entry_set_text(GTK_ENTRY(info->windows->profile->id), prof->first_name);
//     free(p_id);
// }

void mx_upd_prof_build_json_wrapper(t_info *info) {
    upd_prof_bld_json(info, &info->sock->sock);
    mx_wait_for_json(info, success_update_profile, success_update_profile);
    // upd_profile(info);
}
