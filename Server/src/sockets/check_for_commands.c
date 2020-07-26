#include "server.h"

static void list(t_info *info, t_peer *peer, cJSON *jsn) {
    cJSON *bd = mx_get_chat_for_invite(info->sock->db, jsn);
    cJSON *tmp;
    char *buff;
    int len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "users"));

    buff = mx_strjoin_free(strdup(">> "), mx_itoa(len));
    buff = mx_strjoin_free(buff, " users in chat:\n");

    for (int i = 0; i < len; ++i) {
        tmp = cJSON_GetArrayItem(cJSON_GetObjectItem(bd, "users"), i);
        buff = mx_strjoin_free(buff, MX_VSTR(tmp, "login"));
        buff = mx_strjoin_free(buff, ",\n");
    }

    mx_response_db(info, peer, mx_bot_msg(bd, buff));
    mx_strdel(&buff);
}

static void help(t_info *info, t_peer *peer, cJSON *bd) {
    char *buff;

    buff = strdup(">> /ping\t\tServer test\r\n");
    // buff_out = mx_strjoin_free(buff_out, ">> /anime\tWrite a randon anime name\r\n");
    // buff_out = mx_strjoin_free(buff_out, ">> /topic\t\t<message> Set chat topic\r\n");
    buff = mx_strjoin_free(buff, ">> /list\t\tShow active clients\r\n");
    buff = mx_strjoin_free(buff, ">> /help\t\tShow help");

    mx_response_db(info, peer, mx_bot_msg(bd, buff));
    mx_strdel(&buff);
}

static void anime_joke(t_info *info, t_peer *peer, cJSON *bd, char *c) {
    char *buff;

    buff = strdup(">> ");
    if(!strcmp(c, "/anime"))
        buff = mx_strjoin_free(buff, info->sock->anime_list[rand()%99]);
    else if(!strcmp(c, "/joke")) {
        buff = mx_strjoin_free(buff, info->sock->joke_list[rand()%99]);
    }
    mx_response_db(info, peer, mx_bot_msg(bd, buff));
    mx_strdel(&buff);
}

void mx_db_commands(t_info *info, t_peer *peer, cJSON *bd) {
    char *msg;
    char *command;

    if (MX_VSTR(bd, "content")[0] == '/' && MX_TYPE(bd) == send_message) {
        msg = strdup(MX_VSTR(bd, "content"));
        // cJSON_AddStringToObject(bd, "login", "");
        command = strtok(msg, " ");

        if (!strcmp(command, "/ping"))
            mx_response_db(info, peer, mx_bot_msg(bd, ">> pong"));
        else if(!strcmp(command, "/list"))
            list(info, peer, bd);
        else if (!strcmp(command, "/help"))
            help(info, peer, bd);
        else if(!strcmp(command, "/anime") || !strcmp(command, "/joke"))
            anime_joke(info, peer, bd, command);
    }
    // cJSON_Delete(bd);
}
