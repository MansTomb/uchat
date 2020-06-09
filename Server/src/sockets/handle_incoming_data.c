#include "server.h"

void mx_handle_disconnect(t_sock *sock, t_peer *client) {
    //Check if it was for closing , and also read the
    //incoming message
    //Somebody disconnected , get his details and print
    getpeername(client->socket, (struct sockaddr *)&sock->address,
                (socklen_t *)&sock->addrlen);
    printf("Host disconnected, ip %s:%d\n" ,
            inet_ntoa(sock->address.sin_addr), ntohs(sock->address.sin_port));

    //Close the socket and mark as MX_NO_SOCKET in list for reuse
    close(client->socket);
    client->socket = MX_NO_SOCKET;
    mx_dequeue_all(&client->send_buffer);
    client->current_sending_byte   = -1;
    client->current_receiving_byte = 0;
}

// void mx_handle_incoming_data(t_info *info) {
//     int sd = 0;
//     t_sock *sock = info->sock;

//     // else its some IO operation on some other socket
//     for (int i = 0; i < MAX_CLIENTS; ++i) {
//         sd = sock->connection_list[i].socket;
//             if (sd != MX_NO_SOCKET && FD_ISSET(sd, &sock->readfds)) {
//                 // printf("-----");
//                 if ((sock->valread = read(sd, sock->buffer, 1024)) == 0)
//                     mx_handle_disconnect(sock, &sock->connection_list[i]);
//                 else {
//                         // handle_data();
//                     sock->buffer[sock->valread] = '\0';
//                     printf("%s", sock->buffer);
//                     send(sd, sock->buffer, strlen(sock->buffer), 0 );
//                 }
//             }
//     }
// }

void mx_handle_incoming_data(t_info *info) {
    int sd = 0;
    t_sock *sock = info->sock;

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        sd = info->sock->connection_list[i].socket;
        // *client = info->sock->connection_list[i];
        if (sd != MX_NO_SOCKET && FD_ISSET(sd, &info->sock->readfds))
            if (mx_receive_from_peer(info, &sock->connection_list[i],
                                     &mx_handle_received_message) != 0)
                mx_handle_disconnect(sock, &sock->connection_list[i]);
        if (sd != MX_NO_SOCKET && FD_ISSET(sd, &info->sock->writefds))
            if (mx_send_to_peer(info, &sock->connection_list[i]) != 0)
                mx_handle_disconnect(sock, &sock->connection_list[i]);

        if (sd != MX_NO_SOCKET && FD_ISSET(sd, &info->sock->exceptfds)) {
            printf("Exception client fd.\n");
            mx_handle_disconnect(sock, &sock->connection_list[i]);
        }
    }
}
