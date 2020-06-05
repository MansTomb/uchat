#include "server.h"

static void handle_disconnect(t_sock *sock, int *sd, int i) {
    char buffer[1024];
    //Check if it was for closing , and also read the  
    //incoming message  
    if ((sock->valread = read(*sd, buffer, 1024)) == 0)   
    {   
        //Somebody disconnected , get his details and print 
        getpeername(*sd , (struct sockaddr*)&sock->address, (socklen_t*)&sock->addrlen);   
        printf("Host disconnected , ip %s , port %d \n" ,  
                inet_ntoa(sock->address.sin_addr) , ntohs(sock->address.sin_port));   
                
        //Close the socket and mark as 0 in list for reuse  
        close(*sd);   
        sock->client_sockets[i] = 0;   
    }  
}

void mx_handle_incoming_data(t_info *info) {
    int sd = 0;
    t_sock *sock = info->sock;
    // else its some IO operation on some other socket 
    for (int i = 0; i < MAX_CLIENTS; ++i)   
    {   
        sd = sock->client_sockets[i];   
        if (FD_ISSET(sd, &sock->readfds))
            handle_disconnect(sock, &sd, i);
            //Echo back the message that came in  
        // else 
    //     {   
            // Handle incoming data and give answer;
                // handle_data();
    //         buffer[sock->valread] = '\0';   
    //         send(sd , buffer , strlen(buffer) , 0 );   
    //     }   
    }
}   
