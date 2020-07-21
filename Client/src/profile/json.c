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

static void upd_prof_data(const t_info *info) {
    t_profile_data *p = info->cl_data->profile;

    p->first_name = cJSON_GetObjectItemCaseSensitive(info->json, "fname")->valuestring;
    p->sec_name = cJSON_GetObjectItemCaseSensitive(info->json, "sname")->valuestring;
    p->user_email = cJSON_GetObjectItemCaseSensitive(info->json, "email")->valuestring;
    p->status = cJSON_GetObjectItemCaseSensitive(info->json, "status")->valuestring;

    p->sound_noty = cJSON_GetObjectItemCaseSensitive(info->json, "snot")->valueint;
    p->vs_noty = cJSON_GetObjectItemCaseSensitive(info->json, "vnot")->valueint;
    p->email_noty = cJSON_GetObjectItemCaseSensitive(info->json, "enot")->valueint;
}

void mx_clr_profile(t_profile_data *p, int type) {
    if (MX_MALLOC_SIZE(p) > 0) {
        MX_STRDEL(p->first_name);
        MX_STRDEL(p->sec_name);
        MX_STRDEL(p->user_email);
        MX_STRDEL(p->status);
        if (type == 1 && (MX_MALLOC_SIZE(p) > 0))
            free(p);
    }
}

void mx_upd_prof_build_json_wrapper(t_info *info) {
    upd_prof_bld_json(info, &info->sock->sock);
    mx_wait_for_json(info, success_update_profile, failed_update_profile);
    if (mx_get_jtype(info, success_update_profile)) {
        mx_clr_profile(info->cl_data->profile, 0);
        upd_prof_data(info);
    }
}
