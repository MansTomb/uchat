#include "server.h"

static void list(t_info *info, t_peer *peer, cJSON *bd) {
    char buff_out[1024];

    bzero(buff_out, sizeof(buff_out));

    // sprintf(buff_out, ">> clients %d\r\n", a->cli_count);
    // mx_send_msg_self(buff_out, cli->connfd);
    // mx_print_active_clients(a, cli->connfd);

    strcat(buff_out, ">> /ping     Server test\r\n");
    // mx_strcat(buff_out, ">> /topic    <message> Set chat topic\r\n");
    strcat(buff_out, ">> /list     Show active clients\r\n");
    strcat(buff_out, ">> /help     Show help");

    mx_response_db(info, peer, mx_su_msg(bd, buff_out));
}

static void help(t_info *info, t_peer *peer, cJSON *bd) {
    char *buff_out;

    buff_out = strdup(">> /ping\t\tServer test\r\n");
    // buff_out = mx_strjoin_free(buff_out, ">> /anime\tWrite a randon anime name\r\n");
    // buff_out = mx_strjoin_free(buff_out, ">> /topic\t\t<message> Set chat topic\r\n");
    buff_out = mx_strjoin_free(buff_out, ">> /list\t\tShow active clients\r\n");
    buff_out = mx_strjoin_free(buff_out, ">> /help\t\tShow help");

    mx_response_db(info, peer, mx_su_msg(bd, buff_out));
    mx_strdel(&buff_out);
}

void mx_db_commands(t_info *info, t_peer *peer, cJSON *bd) {
    char *msg;
    char *command;

    if (MX_VSTR(bd, "content")[0] == '/' && MX_TYPE(bd) == send_message) {
        msg = strdup(MX_VSTR(bd, "content"));
        cJSON_AddStringToObject(bd, "login", "");
        command = strtok(msg, " ");

        if (!strcmp(command, "/ping"))
            mx_response_db(info, peer, mx_su_msg(bd, ">> pong"));
        else if(!strcmp(command, "/list"))
            mx_response_db(info, peer, mx_su_msg(bd, ">> ANIME NAME"));
        // else if(!strcmp(command, "/list"))
        //     list(info, peer, bd);
        else if (!strcmp(command, "/help"))
            help(info, peer, bd);
        else
            mx_db_send_message(info, peer, bd);
    }
    // cJSON_Delete(bd);
}
