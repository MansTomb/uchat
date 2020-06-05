#include "server.h"

void mx_socketset_clear(t_sock *sock) {
    FD_ZERO(&sock->readfds);   
}

void mx_socket_add_master_to_set(t_sock *sock) {
    FD_SET(sock->master_socket, &sock->readfds);   
    sock->max_sd = sock->master_socket;
}

void mx_socket_add_child_to_set(t_sock *sock) {
    int sd;

    for (int i = 0 ; i < MAX_CLIENTS ; i++) {
        //socket descriptor  
        sd = sock->client_sockets[i];   
                
        //if valid socket descriptor then add to read list  
        if(sd > 0)   
            FD_SET( sd , &sock->readfds);   
                
        //highest file descriptor number, need it for the select function  
        if(sd > sock->max_sd)   
            sock->max_sd = sd;   
    } 
}
