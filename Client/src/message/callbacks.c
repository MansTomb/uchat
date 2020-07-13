#include "client.h"

static void set_text(t_chat *chat, char *content) {
    GtkTextBuffer *buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat->entry));
    GtkTextIter start;
    GtkTextIter end;
    
    gtk_text_buffer_get_start_iter(buff, &start);
    gtk_text_buffer_get_end_iter(buff, &end);
    gtk_text_buffer_delete(buff, &start, &end);
    gtk_text_buffer_set_text(buff, content, strlen(content));
}

void mx_msg_menu_show(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_message *message = data;

    gtk_popover_popup(GTK_POPOVER(message->menu));
}

void mx_msg_delete(GtkWidget *widget, gpointer data) {
    t_message *message = data;

    mx_delete_message_t1_json_wrapper(message);
}

void mx_on_msg_edit(GtkWidget *widget, gpointer data) {
    t_message *message = data;
    t_chat *chat = mx_find_chat(message->info, message->cid);
    GtkWidget *lable;

    lable = gtk_bin_get_child(GTK_BIN(message->msg_bt));

    chat->edit = 1;
    chat->editedmsg = message;
    set_text(chat, (char *)gtk_label_get_text(GTK_LABEL(lable)));
}
