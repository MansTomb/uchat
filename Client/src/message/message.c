#include "client.h"

static void set_preferences(t_message *new, char *msg, int msgheight) {
    GtkWidget *lable;

    lable = gtk_bin_get_child(GTK_BIN(new->msg_bt));
    gtk_widget_set_size_request(new->msg_bt, MX_MSGWIDTH(msg), msgheight / 4);
    gtk_label_set_line_wrap(GTK_LABEL(lable), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(lable), PANGO_WRAP_CHAR);
    gtk_label_set_max_width_chars(GTK_LABEL(lable), 50);
    gtk_label_set_justify(GTK_LABEL(lable), GTK_JUSTIFY_LEFT);
    gtk_label_set_text(GTK_LABEL(lable), msg);

    gtk_widget_set_size_request(new->main_fixed, MX_MSGWIDTH(msg), msgheight / 4);
}

static void json_sets(t_message *msg, cJSON *json, int cid) {
    char *content = cJSON_GetObjectItem(json, "content")->valuestring;
    char *username = cJSON_GetObjectItem(json, "login")->valuestring;
    char *time = cJSON_GetObjectItem(json, "time")->valuestring;

    msg->mid = cJSON_GetObjectItem(json, "mid")->valueint;
    msg->cid = cid;

    set_preferences(msg, content, MX_MSGHEIGHT(content));
    // if (strcmp(username, msg->info->cl_data->profile->login) == 0)
        // gtk_widget_set_margin_start(msg->main_fixed, 400);
    gtk_label_set_text(GTK_LABEL(msg->name_label), username);
    gtk_label_set_text(GTK_LABEL(msg->date_label), time);
}

t_message *mx_message_build(t_info *info, cJSON *json, int cid) {
    t_message *message = malloc(sizeof(t_message));

    message->builder = gtk_builder_new();
    gtk_builder_add_from_file(message->builder, "./Resources/glade/message.glade", NULL);

    message->name_label = mx_gobject_builder(message->builder, "username_label");
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

void mx_message_destroy(t_chat *chat, t_message *msg) {
    gtk_container_remove(GTK_CONTAINER(chat->message_box), gtk_widget_get_parent(msg->main_fixed));
}
