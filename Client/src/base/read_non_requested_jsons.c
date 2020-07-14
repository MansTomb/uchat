#include "client.h"

static void text_message(t_info *info, cJSON *json) {
    int cid = cJSON_GetObjectItem(json, "cid")->valueint;
    t_message *msg = mx_message_build(info, json, cid);

    mx_message_put(info, msg, cid);
    cJSON_Delete(json);
}

static void handlse_send_message(t_info *info, cJSON *json) {
    switch (cJSON_GetObjectItem(json, "type")->valueint) {
        case 1:
            text_message(info, json);
    }
}

static void handle_delete_message(t_info *info, cJSON *json) {
    int cid = cJSON_GetObjectItem(json, "cid")->valueint;
    t_chat *chat = mx_find_chat(info, cid);

    mx_message_destroy(chat, cJSON_GetObjectItem(json, "mid")->valueint);

    cJSON_Delete(json);
}

static void handle_edit_message(t_info *info, cJSON *json) {
    t_chat *chat = mx_find_chat(info, cJSON_GetObjectItem(json, "cid")->valueint);
    t_message *msg = mx_find_message(chat, cJSON_GetObjectItem(json, "mid")->valueint);
    GtkWidget *lable;

    lable = gtk_bin_get_child(GTK_BIN(msg->msg_bt));
    gtk_label_set_text(GTK_LABEL(lable), cJSON_GetObjectItem(json, "content")->valuestring);
}

bool mx_handle_if_not_requested(t_info *info, cJSON *json) {
    switch (cJSON_GetObjectItem(json, "json_type")->valueint) {
        case send_message:
            handlse_send_message(info, json);
            return 0;
        case edit_message:
            handle_edit_message(info, json);
            return 0;
        case delete_message:
            handle_delete_message(info, json);
            return 0;
    }
    cJSON_Delete(json);
    return 1;
}
