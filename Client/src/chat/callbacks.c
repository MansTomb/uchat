#include "client.h"

static char *get_text(t_chat *chat) {
    GtkTextBuffer *buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat->entry));
    GtkTextIter start;
    GtkTextIter end;

    gtk_text_buffer_get_start_iter(buff, &start);
    gtk_text_buffer_get_end_iter(buff, &end);

    return gtk_text_buffer_get_text(buff, &start, &end, FALSE);
}

static void delete_text(t_chat *chat) {
    GtkTextBuffer *buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat->entry));
    GtkTextIter start;
    GtkTextIter end;

    gtk_text_buffer_get_start_iter(buff, &start);
    gtk_text_buffer_get_end_iter(buff, &end);
    gtk_text_buffer_delete(buff, &start, &end);
}

void mx_send_message(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    if (chat->ctype != 3) {
        if (strlen(get_text(chat))) {
            if (chat->edit) {
                mx_edit_message_t1_json_wrapper(chat->editedmsg, get_text(chat));
                chat->edit = 0;
                chat->editedmsg = NULL;
            }
            else
                mx_send_message_t1_json_wrapper(chat, get_text(chat));
        }
        delete_text(chat);
    }
    else
        mx_dialog_warning_create(NULL, "You cant send messages here!");
}

void mx_chat_img_send(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;
    char *name;

    if (chat->ctype != 3) {
        name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chat->img_dialog));
        mx_send_message_t2_json_wrapper(chat, name);

        gtk_widget_hide(chat->img_dialog);
    }
    else
        mx_dialog_warning_create(NULL, "You cant send images here!");
}
