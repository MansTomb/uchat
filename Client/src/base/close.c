#include "client.h"

static void clear_chats(t_info *info) {
    t_chat *node = NULL;

    while (info->chat_list->size) {
        node = mx_get_index(info->chat_list, 0)->data;
        mx_chat_destroy(info, node->cid);
    }
}

static void free_windows(t_info *info) {
    if (info->windows->adm)
        free(info->windows->adm);
    if (info->windows->prof)
        free(info->windows->prof);
    if (info->windows->cont)
        free(info->windows->cont);
    if (info->windows->pref)
        free(info->windows->pref);
    if (info->windows->rc)
        free(info->windows->rc);
    if (info->windows->ac)
        free(info->windows->ac);
    if (info->windows->cp)
        free(info->windows->cp);
    if (info->windows->dp)
        free(info->windows->dp);
    free(info->windows);
}

static void clear_data(t_info *info) {
    mx_clr_custom_lst(info->cl_data->contacts);
    mx_clr_custom_lst(info->cl_data->cont_grp_names);
    free(info->cl_data->profile);
    free(info->cl_data);
}

static void full_destroy(t_info *info) {
    pthread_kill(info->thread.data, 0);
    pthread_kill(info->thread.timer, 0);

    if (info->windows->ms)
        mx_main_screen_destroy(info);
    if (info->windows->log)
        mx_login_screen_destroy(info);
    if (info->windows->reg)
        mx_register_screen_destroy(info);
    if (MX_MALLOC_SIZE(info->json) > 0)
        cJSON_Delete(info->json);
    if (info->response)
        mx_strdel(&info->response);
    clear_chats(info);
    free_windows(info);
    clear_data(info);
    g_timer_destroy(info->timer);
    free(info);
}

gboolean mx_destroy(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_info *info = data;
    
    if (info->wchange == 0) {
        full_destroy(info);
        gtk_main_quit();
        return FALSE;
    }
    return TRUE;
}
