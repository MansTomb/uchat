#include "client.h"

static void attach_layout(t_info *info, t_admin *log) {
    mx_layout_put(info->layout, log->entry_field, 540, 245);
    mx_layout_put(info->layout, log->send_button, 610, 295);
    mx_layout_put(info->layout, log->unlog_button, 520, 295);
}

static void attach_signals(t_info *info, t_admin *log) {
    MX_GSIG_CON(log->send_button, "clicked", MX_CB(mx_admine_send_on_click), info);
    MX_GSIG_CON(log->unlog_button, "clicked", MX_CB(mx_admin_logout_on_click), info);
}

t_admin *mx_admin_constructor(t_info *info) {
    t_admin *new = malloc(sizeof(t_admin));

    if (new) {
        new->entry_field = mx_entry_constructor("admin_entry");
        new->send_button = mx_button_constuctor("Send message to all users", "admin_send");
        new->unlog_button = mx_button_constuctor("Logout", "admin_logout");

        gtk_entry_set_max_length(GTK_ENTRY(new->entry_field), 0);

        mx_css_from_file(info, "./Resources/css/admin.css");
        attach_signals(info, new);
        attach_layout(info, new);
    }
    return new;
}
