#include "server.h"
/*
 * Receive input from client.
 */
static void receive_inp_from_cli(t_all *a, t_client *cli) {
    char *buff_in = mx_init_buff_set_zero(MX_BUFF_SIZE / 2);
    char *buff_out = mx_init_buff_set_zero(MX_BUFF_SIZE);
    int rlen;

    while ((rlen = read(cli->socket, buff_in, MX_BUFF_SIZE - 1)) > 0) {
        buff_in[rlen] = '\0';
        buff_out[0] = '\0';

        mx_strip_newline(buff_in);

        if (!strlen(buff_in))  // ??? Ignore empty buffer
            continue;

        if (buff_in[0] == '/') {
            if (!strncmp(buff_in, "/quit", 5)) {
                // ---------- write about exit, delete cli
                break;
            }
            // else
                // mx_special_opt(a, cli, buff_in, buff_out);
        }
        else {  // Send message.
            snprintf(buff_out, MX_BUFF_SIZE, "[%s] %s\r\n", cli->name, buff_in);
            mx_send_msg_all(a, buff_out, cli->uid);
        }
    }
    mx_strdel(&buff_in);
}
/*
 * Handle all communication with the client.
 */
void *handle_client(void *arg) {
    t_all *a = (t_all *)arg;
    int current_cli;
    t_client *cli = malloc(sizeof(t_client));
    char buff_out[MX_BUFF_SIZE];

    mx_dup_client(a, cli, &current_cli);

    // printf("%s: %d", cli->name, cli->socket);
    sprintf(buff_out, "<< %s has joined", cli->name);
    mx_send_msg_all(a, buff_out, 0);
    // // pthread_mutex_lock(&topic_mutex);
    // if (mx_strlen(a->topic)) {
    //     buff_out[0] = '\0';
    //     sprintf(buff_out, "<< topic: %s\r\n", a->topic);
    //     mx_send_msg_self(buff_out, cli->connfd);
    // }
    // // pthread_mutex_unlock(&topic_mutex);

    mx_send_msg_self("<< see /help for assistance\n", cli->socket);
    receive_inp_from_cli(a, cli);

    /* Close connection */
    sprintf(buff_out, "<< %s has left chatroom\n", cli->name);
    mx_send_msg_all(a, buff_out, cli->uid);
    close(cli->socket);

    // /* Delete client from queue and yield thread */
    // mx_queue_del(a, cli->uid);
    // printf("<< quit ");
    // mx_print_client_addr(cli->addr);
    // printf(" referenced by %d (name - %s)\n", cli->uid, cli->name);
    // free(cli);

    pthread_detach(pthread_self());

    return NULL;
}
