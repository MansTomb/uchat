#include "client.h"

static void attach_layout(t_info *info, t_chat *new) {
    mx_layout_put(info->layout, new->scroll, 300, 100);
    mx_layout_put(info->layout, new->msgentry, 300, 640);
    mx_layout_put(info->layout, new->sendbt, 1080, 640);
    mx_scrollable_container_add(new->scroll, new->box);
}

static void attach_signals(t_chat *new) {
    g_signal_connect(new->msgentry, "activate", G_CALLBACK(mx_send_message), new);
    g_signal_connect(new->sendbt, "clicked", G_CALLBACK(mx_send_message), new);
}

static void set_properties(t_chat *new) {
    gtk_widget_set_size_request(new->msgentry, 780, 40);
    gtk_entry_set_max_length(GTK_ENTRY(new->msgentry), 660);
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(new->box), GTK_SELECTION_NONE);
}

t_chat *mx_chat_constructor(t_info *info) {
    t_chat *new = malloc(sizeof(t_chat));

    if (new) {
        new->scroll = mx_scrollable_constructor("scrollable", 880, 520);
        new->sendbt = mx_button_constuctor("Send", "send_button");
        new->msgentry = mx_entry_constructor("msg_entry");
        new->messages = mx_create_list();
        new->box = mx_listbox_constructor("message_list");
        new->showed_chat = 0;
        new->info = info;
        
        set_properties(new);
        attach_signals(new);
        attach_layout(info, new);
        mx_css_from_file(info, "./Resources/css/chat.css");
    }
    return new;
}