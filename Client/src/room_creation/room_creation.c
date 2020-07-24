#include "client.h"

void mx_room_creation_build(t_info *info, t_room_creation *rc) {
    if (rc == NULL)
        info->windows->rc = rc = malloc(sizeof(t_room_creation));
    else
        return;

    rc->builder = gtk_builder_new();
    gtk_builder_add_from_file(rc->builder, "./Resources/glade/room_creation.glade", NULL);

    rc->dialog = mx_gobject_builder(rc->builder, "dialog");
    rc->createbt = mx_gobject_builder(rc->builder, "create");
    rc->cancelbt = mx_gobject_builder(rc->builder, "cancel");
    rc->entry = mx_gobject_builder(rc->builder, "name");
    rc->roomcheck = mx_gobject_builder(rc->builder, "room");
    rc->channelcheck = mx_gobject_builder(rc->builder, "channel");
    gtk_builder_connect_signals(rc->builder, rc);

    rc->info = info;

    gtk_widget_show(rc->dialog);
}

void mx_room_creation_destroy(t_info *info) {
    gtk_widget_destroy(info->windows->rc->dialog);
    free(info->windows->rc);
    info->windows->rc = NULL;
}
