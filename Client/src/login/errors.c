#include "client.h"

void mx_login_entry_empty(t_info *info) {
    mx_dialog_warning_create(info->main_window, "Fields cant be empty!");
}
