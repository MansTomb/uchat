#include "client.h"

static int wrap(void *data) {
    t_info *info = data;

    mx_create_table(info, info->windows->cont);
    return 0;
}

void mx_handle_ulogin(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    int uid = cJSON_GetObjectItem(json, "uid")->valueint;
    t_contact *contact = mx_find_contant(info, uid);

    if (contact)
        contact->active = 1;
    gdk_threads_add_idle(wrap, info);
}
