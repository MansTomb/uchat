#include "client.h"

void mx_admin_screen_build(t_info *info, t_admin *adm) {
    if (adm == NULL)
        info->windows->adm = adm = malloc(sizeof(t_admin));

    adm->builder = gtk_builder_new();
    gtk_builder_add_from_file(adm->builder, "./Resources/glade/admin_screen.glade", NULL);

    adm->message_tv = GTK_WIDGET(gtk_builder_get_object(adm->builder, "text_view"));
    adm->backbt = GTK_WIDGET(gtk_builder_get_object(adm->builder, "back"));
    adm->sendbt = GTK_WIDGET(gtk_builder_get_object(adm->builder, "send"));
    adm->window = GTK_WIDGET(gtk_builder_get_object(adm->builder, "window"));
    gtk_builder_connect_signals(adm->builder, info);

    gtk_widget_show(adm->window);
}

void mx_admin_screen_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->adm->window);
    free(info->windows->adm);
    info->windows->adm = NULL;
}

static char *get_text(t_admin *adm) {
    GtkTextBuffer *buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(adm->message_tv));
    GtkTextIter start;
    GtkTextIter end;
    
    gtk_text_buffer_get_start_iter(buff, &start);
    gtk_text_buffer_get_end_iter(buff, &end);

    return gtk_text_buffer_get_text(buff, &start, &end, FALSE);
}

static void delete_text(t_admin *adm) {
    GtkTextBuffer *buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(adm->message_tv));
    GtkTextIter start;
    GtkTextIter end;
    
    gtk_text_buffer_get_start_iter(buff, &start);
    gtk_text_buffer_get_end_iter(buff, &end);
    gtk_text_buffer_delete(buff, &start, &end);
}

void mx_on_send_everyone(GtkWidget *widget, gpointer data) {
    t_info *info = data;

    printf("sended %s\n", get_text(info->windows->adm));
    delete_text(info->windows->adm);
}

gboolean mx_admin_on_key_press(GtkWidget *widget, GdkEvent *event, gpointer data) {
    if (event->key.keyval == GDK_KEY_Return && !(event->key.state & GDK_SHIFT_MASK)) {
        mx_on_send_everyone(widget, data);
        return TRUE;
    }
  return FALSE;
}
