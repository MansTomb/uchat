#include "client.h"

json_value *mx_login_build_json(t_info *info) {
    t_login *log = info->current_window;
    json_value *json = json_object_new(0);

    // printf("%s\n", gtk_entry_get_text(GTK_ENTRY(log->username_entry)));
    json_object_push(json, "username", json_string_new(mx_entry_get_text(log->username_entry)));
    json_object_push(json, "password", json_string_new(mx_entry_get_text(log->password_entry)));
    char buffer[1024];

    json_serialize(buffer, json);
    
    if (buffer[0])
        send(info->sock->sock, buffer, strlen(buffer), 0);
    return json;
}
