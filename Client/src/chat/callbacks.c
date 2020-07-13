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
    t_profile_data *prof = chat->info->cl_data->profile;

    // prof->id;
    // chat->cid;
    // type = 1;
    // content = get_text(chat);

    /*
        Твоя фун-ка здесь юра, сверху написано как достать всё что надо для джсон
        Советую в твою ф-ку передать chat, а из него уже в инфо идти бо иначе
        ты не сможешь в get_text(<сюда>) правильный чат
    */

    delete_text(chat);
}

void mx_chat_img_send(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;
    t_profile_data *prof = chat->info->cl_data->profile;

    // prof->id;
    // chat->cid;
    // type = 2;
    // content = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chat->img_dialog);

    /*
        В контенте ебу как там файлы передаються вообмещ ф-кой сверху сможешь
        найти путь к файлу
    */
    gtk_widget_hide(chat->img_dialog);
}
