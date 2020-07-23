#include "client.h"

void mx_ban_user_build(t_info *info, t_chat *chat) {
    t_ban_user *ban = malloc(sizeof(t_ban_user));

    ban->builder = gtk_builder_new();
    gtk_builder_add_from_file(ban->builder, "./Resources/glade/ban_user.glade", NULL);
    ban->dialog = mx_gobject_builder(ban->builder, "dialog");
    ban->entry = mx_gobject_builder(ban->builder, "entry");
    gtk_builder_connect_signals(ban->builder, ban);

    ban->info = info;
    ban->chat = chat;

    gtk_widget_show(ban->dialog);
}

void mx_ban_user_destroy(t_ban_user *ban) {
    gtk_widget_destroy(ban->dialog);
    free(ban);
}
