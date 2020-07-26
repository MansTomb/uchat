#include "client.h"

static int wrap(void *data) {
    t_edit_msg *edit = data;
    GtkWidget *lable;

    lable = gtk_bin_get_child(GTK_BIN(edit->msg->msg_bt));
    gtk_label_set_text(GTK_LABEL(lable), edit->content);
    return 0;
}

void mx_handle_edit_message(t_info *info, cJSON *json) {
    if (!info->windows->ms)
        return;

    t_edit_msg *edit = malloc(sizeof(t_edit_msg));

    edit->chat = mx_find_chat(info, 
                                  cJSON_GetObjectItem(json, "cid")->valueint);
    edit->msg = mx_find_message(edit->chat, 
                                  cJSON_GetObjectItem(json, "mid")->valueint);
    edit->content = cJSON_GetObjectItem(json, "content")->valuestring;
    edit->info = info;

    gdk_threads_add_idle(wrap, edit);
}
