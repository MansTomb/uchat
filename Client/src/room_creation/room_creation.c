#include "client.h"

void mx_room_creation_build(t_info *info, t_room_creation *rc) {
    if (rc == NULL)
        info->windows->rc = rc = malloc(sizeof(t_room_creation));

    rc->builder = gtk_builder_new();
    gtk_builder_add_from_file(rc->builder, "./Resources/glade/room_creation.glade", NULL);

    rc->dialog = GTK_WIDGET(gtk_builder_get_object(rc->builder, "dialog"));
    rc->createbt = GTK_WIDGET(gtk_builder_get_object(rc->builder, "create"));
    rc->cancelbt = GTK_WIDGET(gtk_builder_get_object(rc->builder, "cancel"));
    rc->entry = GTK_WIDGET(gtk_builder_get_object(rc->builder, "name"));
    rc->roomcheck = GTK_WIDGET(gtk_builder_get_object(rc->builder, "room"));
    rc->channelcheck = GTK_WIDGET(gtk_builder_get_object(rc->builder, "channel"));
    gtk_builder_connect_signals(rc->builder, rc);

    rc->info = info;

    gtk_widget_show(rc->dialog);
}

void mx_room_creation_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->rc->dialog);
    free(info->windows->rc);
    info->windows->rc = NULL;
}
