#include "client.h"

static int wrap(void *data) {
    t_del_msg *dmsg = data;

    // mx_message_destroy(dmsg->chat, dmsg->msg);
    gtk_container_remove(GTK_CONTAINER(dmsg->chat->message_box), gtk_widget_get_parent(dmsg->msg->main_fixed));
    mx_pop_index(dmsg->chat->msg_list, dmsg->i);
    free(dmsg->msg);
    free(dmsg);
    return 0;
}
void mx_handle_delete_message(t_info *info, cJSON *json) {
    t_del_msg *dmsg = malloc(sizeof(t_del_msg));
    t_message *node = NULL;

    dmsg->info = info;
    dmsg->chat = mx_find_chat(info, cJSON_GetObjectItem(json, "cid")->valueint);
    dmsg->mid = cJSON_GetObjectItem(json, "mid")->valueint;

    for (size_t i = 0; i < dmsg->chat->msg_list->size; ++i) {
        node = mx_get_index(dmsg->chat->msg_list, i)->data;
        if (node->mid == dmsg->mid) {
            dmsg->msg = node;
            dmsg->i = i;
            gdk_threads_add_idle(wrap, dmsg);
            return;
        }
    }
    cJSON_Delete(json);
}
