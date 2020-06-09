#include "server.h"

void mx_loop_handler(t_info *info) {

    mx_handle_new_connection(info);
    mx_handle_incoming_data(info);
    // mx_handle_stdin_data(info);
}
