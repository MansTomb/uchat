#include "server.h"

/* Reads from stdin and create new message. This message enqueues to send queueu. */
static int read_from_stdin(char *read_buffer, size_t max_len) {
    size_t read_count = 0;
    size_t total_read = 0;

    memset(read_buffer, 0, max_len);
    do {
        read_count = read(STDIN_FILENO, read_buffer, max_len);
        if (read_count < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
            perror("read()");
            return -1;
        }
        else if (read_count < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            break;
        }
        else if (read_count > 0) {
            total_read += read_count;
            if (total_read > max_len) {
                printf("Message too large and will be chopped. Please try to be shorter next time.\n");
                fflush(STDIN_FILENO);
            break;
            }
        }
    } while (read_count > 0);

    size_t len = strlen(read_buffer);

    if (len > 0 && read_buffer[len - 1] == '\n')
        read_buffer[len - 1] = '\0';

    printf("Read from stdin %zu bytes. Let's prepare message to send.\n", strlen(read_buffer));

    return 0;
}

/* Reads from stdin and create new message. This message enqueues to send queueu. */
int mx_handle_read_from_stdin(t_info *info) {
    char read_buffer[MX_DATA_MAXSIZE]; // buffer for stdin

    if (read_from_stdin(read_buffer, MX_DATA_MAXSIZE) != 0)
        return -1;

    // Create new message and enqueue it.
    t_message new_message;
    mx_prepare_message("server_admin", read_buffer, &new_message);
    mx_print_message(&new_message);

    /* enqueue message for all clients */
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (info->sock->connection_list[i].socket != MX_NO_SOCKET) {
            // if (mx_peer_add_to_send(&info->sock->connection_list[i], &new_message) != 0) {
            //     printf("Send buffer was overflowed, we lost this message!\n");
            //     continue;
            // }
        char newbuf[1024];

        sprintf(newbuf, "server_admin: %s", read_buffer);
        send(info->sock->connection_list[i].socket, newbuf, strlen(newbuf), 0);
        // printf("New message to send was enqueued right now.\n");
        }
    }

    return 0;
}
