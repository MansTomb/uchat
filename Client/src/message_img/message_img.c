#include "client.h"

static void json_sets(t_message_img *msg, cJSON *json, int cid) {
    char *content = cJSON_GetObjectItem(json, "content")->valuestring;
    // char *username = cJSON_GetObjectItem(json, "name")->valuestring;
    char *time = cJSON_GetObjectItem(json, "time")->valuestring;
    GtkWidget *image = gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_file_at_scale(content, 200, 200, FALSE, NULL));

    msg->mid = cJSON_GetObjectItem(json, "mid")->valueint;
    msg->cid = cid;

    gtk_button_set_image(GTK_BUTTON(msg->msg_bt), image);
    gtk_label_set_text(GTK_LABEL(msg->name_label), "User");
    gtk_label_set_text(GTK_LABEL(msg->date_label), time);
}

t_message_img *mx_message_img_build(t_info *info, cJSON *json, int cid) {
    t_message_img *message = malloc(sizeof(t_message_img));

    message->builder = gtk_builder_new();
    gtk_builder_add_from_file(message->builder, "./Resources/glade/message_img.glade", NULL);

    message->name_label = GTK_WIDGET(gtk_builder_get_object(message->builder, "username_label"));
    message->date_label = GTK_WIDGET(gtk_builder_get_object(message->builder, "date_label"));
    message->msg_bt = GTK_WIDGET(gtk_builder_get_object(message->builder, "msg_button"));
    message->menu = GTK_WIDGET(gtk_builder_get_object(message->builder, "menu"));
    message->main_fixed = GTK_WIDGET(gtk_builder_get_object(message->builder, "main_fixed"));
    gtk_builder_connect_signals(message->builder, message);

    message->info = info;
    json_sets(message, json, cid);

    gtk_widget_show(message->main_fixed);
    return message;
}

void mx_message_img_destroy(t_chat *chat, t_message_img *msg) {
    gtk_container_remove(GTK_CONTAINER(chat->message_box), gtk_widget_get_parent(msg->main_fixed));
}
