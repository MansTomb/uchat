#include "client.h"

//  All clients chat must be loaded and added here action "mx_get_client_chats"
t_chat_switcher *mx_chat_switcher_constructor(t_info *info) {
    t_chat_switcher *new = malloc(sizeof(t_chat));

    if (new) {
        new->scrollable = mx_scrollable_constructor("scrollabe_of_chat_buttons", 100, 520);
        new->box = mx_box_constructor("box_of_chat_buttons", 80, 40, GTK_ORIENTATION_VERTICAL);

        mx_layout_put(info->layout, new->scrollable, 1180, 100);
        mx_scrollable_container_add(new->scrollable, new->box);

        gtk_widget_set_valign(new->box, GTK_ALIGN_START);
        
        mx_css_from_file(info, "./Resources/css/chat_switcher.css");
    }
    return new;
}
