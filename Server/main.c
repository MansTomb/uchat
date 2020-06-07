#include "server.h"
// Simple example of server with select() and multiple clients.

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>

#include "message.h"

#define MAX_CLIENTS 10

#define NO_SOCKET -1

#define SERVER_NAME "server"

int listen_sock;
peer_t connection_list[MAX_CLIENTS];
char read_buffer[1024]; // buffer for stdin


int main(int argc, char **argv)
// {
//   if (setup_signals() != 0)
//     exit(EXIT_FAILURE);

//   if (start_listen_socket(&listen_sock) != 0)
//     exit(EXIT_FAILURE);

  /* Set nonblock for stdin. */
  int flag = fcntl(STDIN_FILENO, F_GETFL, 0);
  flag |= O_NONBLOCK;
  fcntl(STDIN_FILENO, F_SETFL, flag);

  // int i;
  // for (i = 0; i < MAX_CLIENTS; ++i) {
  //   connection_list[i].socket = NO_SOCKET;
  //   create_peer(&connection_list[i]);
  // }

  // fd_set read_fds;
  // fd_set write_fds;
  // fd_set except_fds;

  // int high_sock = listen_sock;

  // printf("Waiting for incoming connections.\n");

  while (1) {
    // build_fd_sets(&read_fds, &write_fds, &except_fds);

    // high_sock = listen_sock;
    // for (i = 0; i < MAX_CLIENTS; ++i) {
    //   if (connection_list[i].socket > high_sock)
    //     high_sock = connection_list[i].socket;
    // }

    int activity = select(high_sock + 1, &read_fds, &write_fds, &except_fds, NULL);

    switch (activity) {
      case -1:
        perror("select()");
        shutdown_properly(EXIT_FAILURE);

      case 0:
        // you should never get here
        printf("select() returns 0.\n");
        shutdown_properly(EXIT_FAILURE);

      default:
        /* All set fds should be checked. */
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
          if (handle_read_from_stdin() != 0)
            shutdown_properly(EXIT_FAILURE);
        }

        if (FD_ISSET(listen_sock, &read_fds)) {
          handle_new_connection();
        }

        if (FD_ISSET(STDIN_FILENO, &except_fds)) {
          printf("except_fds for stdin.\n");
          shutdown_properly(EXIT_FAILURE);
        }

        if (FD_ISSET(listen_sock, &except_fds)) {
          printf("Exception listen socket fd.\n");
          shutdown_properly(EXIT_FAILURE);
        }

        for (i = 0; i < MAX_CLIENTS; ++i) {
          if (connection_list[i].socket != NO_SOCKET && FD_ISSET(connection_list[i].socket, &read_fds)) {
            if (receive_from_peer(&connection_list[i], &handle_received_message) != 0) {
              close_client_connection(&connection_list[i]);
              continue;
            }
          }

          if (connection_list[i].socket != NO_SOCKET && FD_ISSET(connection_list[i].socket, &write_fds)) {
            if (send_to_peer(&connection_list[i]) != 0) {
              close_client_connection(&connection_list[i]);
              continue;
            }
          }

          if (connection_list[i].socket != NO_SOCKET && FD_ISSET(connection_list[i].socket, &except_fds)) {
            printf("Exception client fd.\n");
            close_client_connection(&connection_list[i]);
            continue;
          }
        }
    }

    printf("And we are still waiting for clients' or stdin activity. You can type something to send:\n");
  }

  return 0;
}
