#include "server.h"

static void topic(t_all *a, t_client *cli, char *buff_out) {
    char *param = strtok(NULL, " ");

    if (param) {
        // pthread_mutex_lock(&a->topic_mutex);
        a->topic[0] = '\0';
        while (param != NULL) {
            mx_strcat(a->topic, param);
            mx_strcat(a->topic, " ");
            param = strtok(NULL, " ");
        }
        // pthread_mutex_unlock(&a->topic_mutex);
        sprintf(buff_out, "<< topic changed to: %s \r\n", a->topic);
        mx_send_msg_all(a, buff_out, -1);
    }
    else {
        mx_send_msg_self("<< message cannot be null\r\n", cli->connfd);
    }
}

static void login(t_all *a, t_client *cli, char *buff_out) {
    char *param = strtok(NULL, " ");
    char *old_name;

    if (param) {
        if (!(old_name = mx_strdup(cli->name))) {
            perror("Cannot allocate memory");
        }
        mx_strcpy(cli->name, param);
        sprintf(buff_out, "<< %s renamed as %s\r\n", old_name, cli->name);
        free(old_name);
        mx_send_msg_all(a, buff_out, -1);
    }
    else {
        mx_send_msg_self("<< name cannot be null\r\n", cli->connfd);
    }
}

static void message(t_all *a, t_client *cli, char *buff_out) {
    char *param = strtok(NULL, " ");
    int uid;

    if (param) {
        uid = atoi(param);
        if ((param = strtok(NULL, " "))) {
            sprintf(buff_out, "[PM][%s]", cli->name);
            while (param != NULL) {
                mx_strcat(buff_out, " ");
                mx_strcat(buff_out, param);
                param = strtok(NULL, " ");
            }
            mx_strcat(buff_out, "\r\n");
            mx_send_msg_client(a, buff_out, uid);
        }
        else
            mx_send_msg_self("<< message cannot be null\r\n", cli->connfd);
    }
    else
        mx_send_msg_self("<< reference cannot be null\r\n", cli->connfd);
}

static void help(t_client *cli, char *buff_out) {
    mx_strcat(buff_out, "<< /quit     Quit chatroom\r\n");
    mx_strcat(buff_out, "<< /ping     Server test\r\n");
    mx_strcat(buff_out, "<< /topic    <message> Set chat topic\r\n");
    mx_strcat(buff_out, "<< /login    <name> Change nickname\r\n");
    mx_strcat(buff_out, "<< /msg      <reference> <message> Send private message\r\n");
    mx_strcat(buff_out, "<< /list     Show active clients\r\n");
    mx_strcat(buff_out, "<< /help     Show help\r\n");
    mx_send_msg_self(buff_out, cli->connfd);
}
/*
 * Special options.
 */
void mx_special_opt(t_all *a, t_client *cli, char *buff_in, char *buff_out) {
    char *command = strtok(buff_in," ");

    if (!mx_strcmp(command, "/ping"))
        mx_send_msg_self("<< pong\r\n", cli->connfd);
    else if (!mx_strcmp(command, "/topic"))
        topic(a, cli, buff_out);
    else if (!strcmp(command, "/login"))
        login(a, cli, buff_out);
    else if (!strcmp(command, "/msg"))
        message(a, cli, buff_out);
    else if(!strcmp(command, "/list")) {
        sprintf(buff_out, "<< clients %d\r\n", a->cli_count);
        mx_send_msg_self(buff_out, cli->connfd);
        mx_print_active_clients(a, cli->connfd);
    }
    else if (!strcmp(command, "/help"))
        help(cli, buff_out);
    else
        mx_send_msg_self("<< unknown command\r\n", cli->connfd);
}
