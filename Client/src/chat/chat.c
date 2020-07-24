#include "client.h"

static void set_jsons(t_chat *chat, cJSON *json) {
    chat->cid = cJSON_GetObjectItem(json, "cid")->valueint;
    chat->role = cJSON_GetObjectItem(json, "role")->valueint;
    chat->ctype = cJSON_GetObjectItem(json, "ctype")->valueint;
    chat->chat_name = cJSON_GetObjectItem(json, "cname")->valuestring;
    mx_save_chat_users(chat, cJSON_GetObjectItem(json, "users"));
}

static void set_data(t_info *info, t_chat *chat, cJSON *json) {
    gtk_builder_connect_signals(chat->builder, chat);
    chat->info = info;
    chat->users = mx_create_list();
    set_jsons(chat, json);
    mx_set_chat_preferences(chat);
    chat->edit = 0;
    if (chat->ctype == 1)
        gtk_widget_hide(chat->unbanbt);
    gtk_widget_show(chat->main_box);
}

t_chat *mx_chat_build(t_info *info, cJSON *json) {
    t_chat *chat = malloc(sizeof(t_chat));

    chat->builder = gtk_builder_new();
    gtk_builder_add_from_file(chat->builder, "./Resources/glade/chat.glade", NULL);
    chat->entry = mx_gobject_builder(chat->builder, "entry");
    chat->banbt = mx_gobject_builder(chat->builder, "ban");
    chat->unbanbt = mx_gobject_builder(chat->builder, "unban");
    chat->invbt = mx_gobject_builder(chat->builder, "invite");
    chat->leavebt = mx_gobject_builder(chat->builder, "leave");
    chat->sendbt = mx_gobject_builder(chat->builder, "send");
    chat->sendimgbt = mx_gobject_builder(chat->builder, "sendimg");
    chat->main_box = mx_gobject_builder(chat->builder, "main_box");
    chat->message_box = mx_gobject_builder(chat->builder, "message_box");
    chat->img_dialog = mx_gobject_builder(chat->builder, "img_dialog");
    chat->ffilter = GTK_FILE_FILTER(gtk_builder_get_object(chat->builder, "filter"));
    chat->msg_list = mx_create_list();
    set_data(info, chat, json);
    return chat;
}

void mx_chat_destroy(t_info *info, int cid) {
    t_chat *chat = NULL;
    size_t i = 0;

    for (; i < info->chat_list->size; ++i) {
        chat = mx_get_index(info->chat_list, i)->data;
        if (chat->cid == cid)
            break;
    }
    gtk_widget_destroy(chat->main_box);
    mx_clr_custom_lst(chat->users);
    free(chat);
    mx_pop_index(info->chat_list, i);
}
