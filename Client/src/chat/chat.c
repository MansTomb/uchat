#include "client.h"

static void clear_list_elem(t_list_node *node) {
    t_list_node *next = node->next;
    t_list_node *prev = node->prev;

    prev->next = next;
    next->prev = prev;
    
    free(node);
}

static void show_all_messages(t_list_node *node) {
    if (node->data)
        mx_chat_show_message(node->data);
    else
        clear_list_elem(node);
    // printf("%p", (void *)node->data);
}

static void hide_all_messages(t_list_node *node) {
    if (node->data)
        mx_chat_hide_message(node->data);
    else
        clear_list_elem(node);
    // printf("%p", (void *)node->data);
}

void mx_chat_screen_show(t_chat *chat) {
    gtk_widget_show(chat->scroll);
    gtk_widget_show(chat->box);
    gtk_widget_show(chat->sendbt);
    gtk_widget_show(chat->msgentry);
    chat->showed_chat = 1;
    mx_foreach_list(chat->messages, show_all_messages);
}
void mx_chat_screen_hide(t_chat *chat) {
    gtk_widget_hide(chat->scroll);
    gtk_widget_hide(chat->box);
    gtk_widget_hide(chat->sendbt);
    gtk_widget_hide(chat->msgentry);
    chat->showed_chat = 0;
    mx_foreach_list(chat->messages, hide_all_messages);
}

void mx_chat_message_put(t_chat *chat, t_message *message) {
    // GtkWidget *fxd = mx_fixed_constructor("fixed", 200, 40);
    // GtkWidget *bt = mx_button_constuctor(text, "anme");

    // GtkWidget *lable = gtk_bin_get_child(GTK_BIN(bt));
    // mx_fixed_put(fxd, bt, 0, 0);
    // gtk_widget_set_size_request(bt, 200, 50);
    // gtk_label_set_line_wrap(GTK_LABEL(lable), TRUE);
    // gtk_label_set_line_wrap_mode(GTK_LABEL(lable), PANGO_WRAP_CHAR);
    // gtk_label_set_selectable(GTK_LABEL(lable), TRUE);
    // gtk_label_set_max_width_chars(GTK_LABEL(lable), 200);
    // gtk_widget_show(fxd);
    // printf("privet %s", gtk_label_get_text(GTK_LABEL(lable)));
    // gtk_widget_show(bt);
    // gtk_list_box_insert(GTK_LIST_BOX(chat->box), bt, -1);
    mx_push_back(chat->messages, message);
    gtk_list_box_insert(GTK_LIST_BOX(chat->box), message->frame, -1);
    mx_chat_screen_show(chat);
}
