#include "server.h"

void mx_loop_handler(t_info *info) {

    mx_handle_new_connection(info);
    mx_handle_incoming_data(info);

    /* All set fds should be checked. */
    // if (FD_ISSET(STDIN_FILENO, &read_fds)) {
    //   if (handle_read_from_stdin() != 0)
    //     shutdown_properly(EXIT_FAILURE);
    // }

//         if (FD_ISSET(STDIN_FILENO, &except_fds)) {
//           printf("except_fds for stdin.\n");
//           shutdown_properly(EXIT_FAILURE);
//         }

//         if (FD_ISSET(listen_sock, &except_fds)) {
//           printf("Exception listen socket fd.\n");
//           shutdown_properly(EXIT_FAILURE);
//         }

//         for (i = 0; i < MAX_CLIENTS; ++i) {
//           if (connection_list[i].socket != NO_SOCKET && FD_ISSET(connection_list[i].socket, &read_fds)) {
//             if (receive_from_peer(&connection_list[i], &handle_received_message) != 0) {
//               close_client_connection(&connection_list[i]);
//               continue;
//             }
//           }

//           if (connection_list[i].socket != NO_SOCKET && FD_ISSET(connection_list[i].socket, &write_fds)) {
//             if (send_to_peer(&connection_list[i]) != 0) {
//               close_client_connection(&connection_list[i]);
//               continue;
//             }
//           }

//           if (connection_list[i].socket != NO_SOCKET && FD_ISSET(connection_list[i].socket, &except_fds)) {
//             printf("Exception client fd.\n");
//             close_client_connection(&connection_list[i]);
//             continue;
//           }
//         }
//     }

//     printf("And we are still waiting for clients' or stdin activity. You can type something to send:\n");

}
