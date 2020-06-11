#include "client.h"

static void attach_signals(t_info *info, t_room_creation *new) {
    g_signal_connect(GTK_TOGGLE_BUTTON(new->channelbt), "toggled",
                     G_CALLBACK(mx_on_click_create_room_channel), info);
    g_signal_connect(GTK_TOGGLE_BUTTON(new->groupbt), "toggled",
                     G_CALLBACK(mx_on_click_create_room_group), info);
    g_signal_connect(new->create, "clicked",
                     G_CALLBACK(mx_on_click_create_room_create), info);
    g_signal_connect(new->cancel, "clicked",
                     G_CALLBACK(mx_on_click_create_room_cancel), info);
}

static void attach_layout(t_room_creation *new, GtkWidget *fixed) {
    gtk_fixed_put(GTK_FIXED(fixed), new->groupbt, 20, 40);
    gtk_fixed_put(GTK_FIXED(fixed), new->channelbt, 120, 40);
    gtk_fixed_put(GTK_FIXED(fixed), new->entry, 10, 80);
    gtk_fixed_put(GTK_FIXED(fixed), new->type, 10, 20);
    gtk_fixed_put(GTK_FIXED(fixed), new->create, 10, 120);
    gtk_fixed_put(GTK_FIXED(fixed), new->cancel, 160, 120);
}

static void show(t_info *info, t_room_creation *new, GtkWidget *fixed) {
    info->windows->room_creation = new;
    attach_signals(info, new);
    attach_layout(new, fixed);
    gtk_widget_set_size_request(new->dialog, 240, 160);
    gtk_widget_show(new->dialog);
    gtk_widget_show(new->cancel);
    gtk_widget_show(new->create);
    gtk_widget_show(new->type);
    gtk_widget_show(new->entry);
    gtk_widget_show(new->groupbt);
    gtk_widget_show(new->channelbt);
    gtk_widget_show(fixed);
}

t_room_creation *mx_room_creation_constructor(t_info *info) {
    t_room_creation *new = malloc(sizeof(t_room_creation));
    GtkWidget *action_area;
    GtkWidget *fixed;

    if (new && info) {
        new->dialog = gtk_dialog_new();
        new->groupbt = gtk_check_button_new_with_label("Group");
        new->channelbt = gtk_check_button_new_with_label("Channel");
        new->entry = mx_entry_constructor("create_room_entry");
        new->type = mx_label_constructor("create_room_label", "Choose type of room to create");
        new->cancel = mx_button_constuctor("Cancel", "create_room_cancel");
        new->create = mx_button_constuctor("Create", "create_room_create");
        action_area = gtk_dialog_get_content_area(GTK_DIALOG(new->dialog));
        fixed = mx_fixed_constructor("create_room_fixed", 240, 160);
        gtk_container_add(GTK_CONTAINER(action_area), fixed);
        gtk_window_set_position (GTK_WINDOW(new->dialog), GTK_WIN_POS_CENTER);
        show(info, new, fixed);
    }
    return new;
}

void mx_room_creation_destructor(t_info *info) {
    t_room_creation *room_creation = info->windows->room_creation;

    gtk_widget_destroy(room_creation->cancel);
    gtk_widget_destroy(room_creation->create);
    gtk_widget_destroy(room_creation->type);
    gtk_widget_destroy(room_creation->entry);
    gtk_widget_destroy(room_creation->groupbt);
    gtk_widget_destroy(room_creation->channelbt);
    gtk_widget_destroy(room_creation->dialog);
    info->windows->room_creation = NULL;
}
