#include "client.h"

static int wrap2(void *data) {
    t_send_msg_img *msg = data;

    msg->chat = mx_find_chat(msg->info, msg->cid);
    if (msg->chat) {
        msg->msg = mx_message_img_build(msg->info, msg->json, msg->cid);
        mx_push_front(msg->chat->msg_list, msg->msg);
        gtk_list_box_insert(GTK_LIST_BOX(msg->chat->message_box),
                                                    msg->msg->main_fixed, -1);
        mx_set_vnoti(msg->info, msg->info->windows->ms, msg->cid, 1);
        mx_snotify(msg->info, msg->info->windows->ms, msg->cid);
    }
    free(msg);
    return 0;
}

void mx_handle_img_message(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    t_send_msg_img *msg = malloc(sizeof(t_send_msg));

    msg->cid = cJSON_GetObjectItem(json, "cid")->valueint;
    msg->json = json;
    msg->info = info;
    gdk_threads_add_idle(wrap2, msg);
}
