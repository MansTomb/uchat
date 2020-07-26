#include "client.h"

t_sock *mx_client_socket_create(char *ip, int port) {
    t_sock *new = malloc(sizeof(t_sock));

    if ((new->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket Creation Error\n");
        exit(EXIT_FAILURE);
    }
    new->serv_addr.sin_family = AF_INET;
    new->serv_addr.sin_port = htons(port);
    if(inet_pton(AF_INET, ip, &new->serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        exit(EXIT_FAILURE);
    }
    if (connect(new->sock, 
            (struct sockaddr *)&new->serv_addr, sizeof(new->serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        exit(EXIT_FAILURE);
    }
    return new;
}
