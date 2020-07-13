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
    t_message *msg = mx_message_build(chat->info, "4Elovek", get_text(chat));

    delete_text(chat);
    gtk_list_box_insert(GTK_LIST_BOX(chat->message_box), msg->main_fixed, -1);
}

gboolean mx_on_key_press(GtkWidget *widget, GdkEvent *event, gpointer data) {
    t_chat *chat = data;

    if (event->key.keyval == GDK_KEY_Return && !(event->key.state & GDK_SHIFT_MASK)) {
        mx_send_message(widget, data);
        return TRUE;
    }
    return FALSE;
}

void mx_chat_img_send(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;
    GtkWidget *img = gtk_image_new_from_animation(gdk_pixbuf_animation_new_from_file(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chat->img_dialog)), NULL));
    t_message_img *msg = mx_message_img_build(chat->info, "4Elovek", img);

    gtk_list_box_insert(GTK_LIST_BOX(chat->message_box), msg->main_fixed, -1);
    gtk_widget_hide(chat->img_dialog);
}

void mx_choose_dialog(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    gtk_widget_show(chat->img_dialog);
}

void mx_on_dialog_cancel(GtkWidget *widget, gpointer data) {
    t_chat *chat = data;

    gtk_widget_hide(chat->img_dialog);
}

void mx_on_scroll_edge(GtkWidget *widget, GtkPositionType pos, gpointer data) {
    t_chat *chat = data;

    printf("Load messages netop\n");
    if (GTK_POS_TOP == pos) {
        printf("Load messages\n");
        /* Load message */
    }
}
