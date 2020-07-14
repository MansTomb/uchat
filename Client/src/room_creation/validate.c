#include "client.h"

static gboolean get_active(GtkWidget *widget) {
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
}

static gboolean validate_toggle_buttons(t_room_creation *room) {
    if ((get_active(room->channelcheck)
        && !get_active(room->roomcheck))
        || (!get_active(room->channelcheck)
        && get_active(room->roomcheck)))
        return true;
    return false;
}

gboolean mx_room_creation_data_validation(t_room_creation *room) {
    if (!mx_entry_text_exist(room->entry))
        mx_dialog_warning_create(NULL, "Room must have name!");
    else if (!validate_toggle_buttons(room))
        mx_dialog_warning_create(NULL, "Choose type for chat!");
    else
        return true;
    return false;
}
