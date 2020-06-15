#include "client.h"

#define text ".messageframe label {\n    color: white;\n    text-shadow: 10px 10px 10px black, 1px 1px 1px turquoise;\n    font-size: 40px;\n}"
#define text2 ".messagemessageframe label {    color: white; oahfoihfinqlfnih wi hrighwg higheipgqhe gpqehg eoghewgehgwepighwgewkghweigwmessageframe label {    color: white; oahfoihfinqlfnih wi hrighwg higheipgqhe gpqehg eoghewgehgwepighwgewkghweigwframe label {    color: white; oahfoihfinqlfnih wi hrighwg higheipgqhe gpqehg eoghewgehgwepighwgewkghweigw"
#define text3 " kak soobweniya viglyadat"

void mx_main_chat_screen_show(t_info *info) {
    if (!info->windows->chat_switcher)
        info->windows->chat_switcher = mx_chat_switcher_constructor(info);

    info->current_window = info->windows->chat_switcher;
    mx_css_from_file(info, "./Resources/css/chat.css");
    //подтянуть чаты но пока заглушка -----------------
    mx_push_back(info->chat_list, mx_chat_constructor(info));
    mx_push_back(info->chat_list, mx_chat_constructor(info));
    // mx_push_back(info->chat_list, mx_chat_constructor(info));

    t_message *one = mx_message_construct(info, text, "Loh1");
    t_message *one2 = mx_message_construct(info, text2, "Loh1");
    // t_message *one3 = mx_message_construct(info, text2, "Heh");
    t_message *one4 = mx_message_construct(info, text2, "Heh");
    t_message *one5 = mx_message_construct(info, text2, "Heh");
    // t_message *one6 = mx_message_construct(info, text2, "blyat");

    mx_chat_switcher_add_chat(info, (t_chat *)mx_get_index(info->chat_list, 0)->data, "general");
    mx_chat_switcher_add_chat(info, (t_chat *)mx_get_index(info->chat_list, 1)->data, "new1");
    // mx_chat_switcher_add_chat(info, (t_chat *)mx_get_index(info->chat_list, 2)->data, "new2");

    mx_chat_message_put((t_chat *)mx_get_index(info->chat_list, 0)->data, one);
    mx_chat_message_put((t_chat *)mx_get_index(info->chat_list, 1)->data, one2);
    mx_chat_message_put((t_chat *)mx_get_index(info->chat_list, 1)->data, one4);
    mx_chat_message_put((t_chat *)mx_get_index(info->chat_list, 1)->data, one5);
    // mx_chat_message_put((t_chat *)mx_get_index(info->chat_list, 2)->data, one6);
    // mx_chat_message_put((t_chat *)mx_get_index(info->chat_list, 2)->data, one3);
    // ---------------------------------------------------------------------------- это всё заглушка
    mx_main_menu_show(info);
    mx_chat_switcher_show(info);
}

void mx_main_chat_screen_hide(t_info *info) {
    if (!info->windows->chat_switcher)
        info->windows->chat_switcher = mx_chat_switcher_constructor(info);

    info->current_window = NULL;

    mx_chat_switcher_hide(info);
}
