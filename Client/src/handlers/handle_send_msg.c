#include "client.h"

static int wrap(void *data) {
    t_send_msg *msg = data;

    msg->chat = mx_find_chat(msg->info, msg->cid);
    msg->msg = mx_message_build(msg->info, msg->json, msg->cid);

    mx_push_front(msg->chat->msg_list, msg->msg);
    gtk_list_box_insert(GTK_LIST_BOX(msg->chat->message_box),
                                                     msg->msg->main_fixed, -1);
    mx_set_vnoti(msg->info, msg->info->windows->ms, msg->cid, 1);
    mx_snotify(msg->info, msg->info->windows->ms, msg->cid);
    free(msg);
    return 0;
}

static void text_message(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    t_send_msg *msg = malloc(sizeof(t_send_msg));

    msg->cid = cJSON_GetObjectItem(json, "cid")->valueint;
    msg->info = info;
    msg->json = json;
    gdk_threads_add_idle(wrap, msg);
}

void mx_handle_send_message(t_info *info, cJSON *json) {
    int type = cJSON_GetObjectItem(json, "type")->valueint;
    switch (type) {
        case 1:
            text_message(info, json);
            break;
        case 2:
            mx_handle_img_message(info, json);
            break;
    }
}
