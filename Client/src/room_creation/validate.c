#include "client.h"

// static gboolean validate_toggle_buttons(t_room_creation *room) {
//     if ((mx_toggle_get_active(room->channelbt)
//         && !mx_toggle_get_active(room->groupbt))
//         || (!mx_toggle_get_active(room->channelbt)
//         && mx_toggle_get_active(room->groupbt)))
//         return true;
//     return false;
// }

// gboolean mx_room_creation_data_validation(t_room_creation *room) {
//     if (!mx_entry_text_exist(room->entry))
//         mx_dialog_warning_create(NULL, "Room must have name!");
//     else if (!validate_toggle_buttons(room))
//         mx_dialog_warning_create(NULL, "Choose type for chat!");
//     else
//         return true;
//     return false;
// }
