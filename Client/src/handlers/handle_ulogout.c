#include "client.h"

static int wrap(void *data) {
    t_info *info = data;

    mx_create_table(info, info->windows->cont);
    return 0;
}

void mx_handle_ulogout(t_info *info, cJSON *json) {
    int uid = cJSON_GetObjectItem(json, "uid")->valueint;
    t_contact *contact = mx_find_contant(info, uid);

    contact->active = 0;
    gdk_threads_add_idle(wrap, info);
}
