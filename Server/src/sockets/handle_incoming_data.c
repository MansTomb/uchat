#include "server.h"

static void handle_disconnect(t_sock *sock, int *sd, int i) {
    //Check if it was for closing , and also read the
    //incoming message
    //Somebody disconnected , get his details and print
    getpeername(*sd , (struct sockaddr*)&sock->address, (socklen_t*)&sock->addrlen);
    printf("Host disconnected , ip %s , port %d \n" ,
            inet_ntoa(sock->address.sin_addr) , ntohs(sock->address.sin_port));

    //Close the socket and mark as 0 in list for reuse
    close(*sd);
    sock->connection_list[i].socket = MX_NO_SOCKET;
}

void mx_handle_incoming_data(t_info *info) {
    int sd = 0;
    t_sock *sock = info->sock;
    // else its some IO operation on some other socket
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        sd = sock->connection_list[i].socket;
            if (FD_ISSET(sd, &sock->readfds)) {
                // printf("-----");
                if ((sock->valread = read(sd, sock->buffer, 1024)) == 0)
                    handle_disconnect(sock, &sd, i);
                else {
                        // handle_data();
                    sock->buffer[sock->valread] = '\0';
                    printf("%s", sock->buffer);
                    // send(sd , buffer , strlen(buffer) , 0 );
                }
            }
    }
}
