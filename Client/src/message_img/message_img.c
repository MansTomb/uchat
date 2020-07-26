#include "client.h"

static GtkWidget *get_image_if_image(cJSON *json) {
    char *content = cJSON_GetObjectItem(json, "content")->valuestring;
    char *path = mx_strjoin(MX_RECV_FILES_DIR, (content + 11));
    GdkPixbufAnimation *anim = NULL;
    GtkWidget *image = NULL;

    if (strstr(content, ".png") || strstr(content, ".jpg")
     || strstr(content, ".mbp") || strstr(content, ".jpeg")
     || strstr(content, ".gif")) {
        anim = gdk_pixbuf_animation_new_from_file(path, NULL);
        image = gtk_image_new_from_animation(anim);
        return image;
    }
    mx_strdel(&path);
    return image;
}

static void json_sets(t_message_img *msg, cJSON *json, int cid) {
    char *content = cJSON_GetObjectItem(json, "content")->valuestring;
    char *username = cJSON_GetObjectItem(json, "login")->valuestring;
    char *time = cJSON_GetObjectItem(json, "time")->valuestring;
    GtkWidget *image = get_image_if_image(json);

    msg->mid = cJSON_GetObjectItem(json, "mid")->valueint;
    msg->cid = cid;
    if (image)
        gtk_button_set_image(GTK_BUTTON(msg->msg_bt), image);
    else
        gtk_button_set_label(GTK_BUTTON(msg->msg_bt), MX_RECV_FILES_DIR);
    gtk_label_set_text(GTK_LABEL(msg->name_label), username);
    gtk_label_set_text(GTK_LABEL(msg->date_label), time);
}

t_message_img *mx_message_img_build(t_info *info, cJSON *json, int cid) {
    t_message_img *message = malloc(sizeof(t_message_img));

    message->builder = gtk_builder_new();
    gtk_builder_add_from_file(message->builder, MX_GLADE_MSGIMG, NULL);

    message->name_label = mx_gobject_builder(message->builder, 
                                                            "username_label");
    message->date_label = mx_gobject_builder(message->builder, "date_label");
    message->msg_bt = mx_gobject_builder(message->builder, "msg_button");
    message->menu = mx_gobject_builder(message->builder, "menu");
    message->main_fixed = mx_gobject_builder(message->builder, "main_fixed");
    gtk_builder_connect_signals(message->builder, message);
    message->info = info;
    json_sets(message, json, cid);
    gtk_widget_show(message->main_fixed);
    return message;
}

void mx_message_img_destroy(t_chat *chat, t_message_img *msg) {
    gtk_container_remove(GTK_CONTAINER(chat->message_box),
                                       gtk_widget_get_parent(msg->main_fixed));
    free(msg);
}
