#include "client.h"

void mx_chat_screen_show(t_info *info) {
    t_chat *chat = info->windows->chat;

    if (chat == NULL)
        chat = info->windows->chat = mx_chat_constructor(info);

    gtk_widget_show(chat->scroll);
    gtk_widget_show(chat->layout);
    gtk_widget_show(chat->stack);
    gtk_widget_show(chat->stack_controller);
    printf("privet\n");
    mx_background_image_show(chat->back_image);
}
void mx_chat_screen_hide(t_info *info) {
    t_chat *chat = info->windows->chat;

    gtk_widget_hide(chat->layout);
    mx_background_image_hide(chat->back_image);
}
