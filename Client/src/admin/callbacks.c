#include "client.h"

static char *get_text(t_admin *adm) {
    GtkTextBuffer *buff = gtk_text_view_get_buffer(
                                            GTK_TEXT_VIEW(adm->message_tv));
    GtkTextIter start;
    GtkTextIter end;
    
    gtk_text_buffer_get_start_iter(buff, &start);
    gtk_text_buffer_get_end_iter(buff, &end);

    return gtk_text_buffer_get_text(buff, &start, &end, FALSE);
}

static void delete_text(t_admin *adm) {
    GtkTextBuffer *buff = gtk_text_view_get_buffer(
                                            GTK_TEXT_VIEW(adm->message_tv));
    GtkTextIter start;
    GtkTextIter end;
    
    gtk_text_buffer_get_start_iter(buff, &start);
    gtk_text_buffer_get_end_iter(buff, &end);
    gtk_text_buffer_delete(buff, &start, &end);
}

void mx_on_send_everyone(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_admin_send_wrapper(info, get_text(info->windows->adm));
    delete_text(info->windows->adm);
}

void mx_admin_exit(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    mx_destroy(NULL, NULL, info);
}

gboolean mx_admin_on_key_press(GtkWidget *widget, GdkEvent *event,
                                                 gpointer data) {
    if (event->key.keyval == GDK_KEY_Return &&
      !(event->key.state & GDK_SHIFT_MASK)) {
        mx_on_send_everyone(widget, data);
        return TRUE;
    }
  return FALSE;
}
