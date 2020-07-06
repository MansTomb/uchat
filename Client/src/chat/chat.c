#include "client.h"

t_chat *mx_chat_build(t_info *info, char *chat_name) {
    t_chat *chat = malloc(sizeof(t_chat));

    chat->builder = gtk_builder_new();
    gtk_builder_add_from_file(chat->builder, "./Resources/glade/chat.glade", NULL);

    chat->entry = GTK_WIDGET(gtk_builder_get_object(chat->builder, "entry"));
    chat->main_box = GTK_WIDGET(gtk_builder_get_object(chat->builder, "main_box"));
    chat->message_box = GTK_WIDGET(gtk_builder_get_object(chat->builder, "message_box"));
    chat->img_dialog = GTK_WIDGET(gtk_builder_get_object(chat->builder, "img_dialog"));
    chat->ffilter = GTK_FILE_FILTER(gtk_builder_get_object(chat->builder, "filter"));
    gtk_builder_connect_signals(chat->builder, chat);
    gtk_file_filter_add_pixbuf_formats(chat->ffilter);

    chat->chat_name = chat_name;
    chat->info = info;

    gtk_widget_show(chat->main_box);
    return chat;
}

void mx_chat_destroy(t_list_node *chat_node) {
    t_chat *chat = chat_node->data;
    t_list_node *next = chat_node->next;
    t_list_node *prev = chat_node->prev;

    gtk_widget_destroy(chat->main_box);
    free(chat_node->data);
    
    prev->next = next;
    next->prev = prev;
}

// static void free_wrapper(char **str, cJSON **jmessage) {
//     cJSON_Delete(*jmessage);
//     if (MX_MALLOC_SIZE(*str))
//         free(*str);
// }

// static void send_messege_json(const t_info *info, int s_sock) {
//     cJSON *jmessage = cJSON_CreateObject();
//     char *str = NULL;

//     cJSON_AddNumberToObject(jmessage, "json_type", send_message);
//     cJSON_AddNumberToObject(jmessage, "uid", info->cl_data->profile->id);
//     cJSON_AddNumberToObject(jmessage, "chat_id", 1);
//     cJSON_AddNumberToObject(jmessage, "type", 1);
//     // cJSON_AddStringToObject(jmessage, "content", info->);

//     str = cJSON_Print(jmessage);
//     if (!str || send(s_sock, str, strlen(str), 0) == -1)
//         fprintf(stderr, "login: 'send' error occured\n");
//     free_wrapper(&str, &jmessage);
// }

// void mx_login_build_json_wrapper(t_info *info) {
//     send_messege_json(info, info->sock->sock);
// }
