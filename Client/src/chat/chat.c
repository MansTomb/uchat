#include "client.h"

static void set_jsons(t_chat *chat, cJSON *json) {
    chat->cid = cJSON_GetObjectItem(json, "cid")->valueint;
    chat->ctype = cJSON_GetObjectItem(json, "ctype")->valueint;
    chat->chat_name = cJSON_GetObjectItem(json, "cname")->valuestring;
    chat->role = cJSON_GetObjectItem(json, "role")->valueint;
}

static void set_preferences(t_chat *chat) {
    if (chat->ctype == 2) {
        if (chat->role == 1) {
            gtk_widget_hide(chat->banbt);
            gtk_widget_hide(chat->invbt);
        }
        else if (chat->role == -1) {
            gtk_widget_hide(chat->banbt);
            gtk_widget_hide(chat->invbt);
            gtk_widget_hide(chat->entry);
        }
    }
    else if (chat->ctype == 3) {
        if (chat->role != 2) {
            gtk_widget_hide(chat->banbt);
            gtk_widget_hide(chat->invbt);
            gtk_widget_hide(chat->entry);
        }
    }
}

t_chat *mx_chat_build(t_info *info, cJSON *json) {
    t_chat *chat = malloc(sizeof(t_chat));

    chat->builder = gtk_builder_new();
    gtk_builder_add_from_file(chat->builder, "./Resources/glade/chat.glade", NULL);

    chat->entry = GTK_WIDGET(gtk_builder_get_object(chat->builder, "entry"));
    chat->banbt = GTK_WIDGET(gtk_builder_get_object(chat->builder, "bat"));
    chat->invbt = GTK_WIDGET(gtk_builder_get_object(chat->builder, "invite"));
    chat->main_box = GTK_WIDGET(gtk_builder_get_object(chat->builder, "main_box"));
    chat->message_box = GTK_WIDGET(gtk_builder_get_object(chat->builder, "message_box"));
    chat->img_dialog = GTK_WIDGET(gtk_builder_get_object(chat->builder, "img_dialog"));
    chat->ffilter = GTK_FILE_FILTER(gtk_builder_get_object(chat->builder, "filter"));
    chat->msg_list = mx_create_list();
    gtk_builder_connect_signals(chat->builder, chat);
    gtk_file_filter_add_pixbuf_formats(chat->ffilter);

    set_jsons(chat, json);
    set_preferences(chat);
    chat->edit = 0;
    chat->info = info;

    gtk_widget_show(chat->main_box);
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
    mx_strdel(&chat->chat_name);
    gtk_widget_destroy(chat->main_box);
    free(chat);
    mx_pop_index(info->chat_list, i);
}
