#include "server.h"

static int *get_arr(cJSON *bd) {
    int len;
    int *uid;

    len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
    uid = malloc((len + 1) * sizeof(int));
    for (int i = 0; i < len; ++i)
        uid[i] = cJSON_GetNumberValue
                (cJSON_GetArrayItem(cJSON_GetObjectItem(bd, "clients_id"), i));
    uid[len] = -1;

    return uid;
}

static int *get_arr_exept(cJSON *bd) {
    int len;
    int *uid;
    int id;

    len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
    uid = malloc((len + 1 - 1) * sizeof(int));
    for (int i = 0; i < len; ++i) {
        id = cJSON_GetNumberValue(cJSON_GetArrayItem(
            cJSON_GetObjectItem(bd, "clients_id"), i));
        if (id != MX_VINT(bd, "uid"))
            uid[i] = id;
    }
    uid[len - 1] = -1;

    return uid;
}

void mx_db_invite_send_message(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;
    int *uid;
    int len;
    int id = 0;

    bd = mx_invite(info->sock->db, get);
    printf("%s", cJSON_Print(bd));
    if (MX_TYPE(bd) == failed_add_user_in_chat)
        mx_send_message_handler(info->sock, peer, bd, peer->socket);
    else {
        len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
        uid = get_arr_exept(bd);
        mx_send_msg_clients(info->sock, peer, bd, uid);
        bd = mx_get_chat_for_invite(info->sock->db, bd);
        printf("%s", cJSON_Print(bd));
        mx_send_msg_client(info->sock, peer, bd, MX_VINT(bd, "uid"));
        mx_response_db(info, peer,
                       mx_server_msg(bd, " явил свою личность в этом чате!"));
        free(uid);
    }
    cJSON_Delete(bd);
}

void mx_db_leave_send_message(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;
    int *uid;
    int len;
    int id = 0;

    bd = mx_leave_chat(info->sock->db, get);
    printf("%s", cJSON_Print(bd));
    if (MX_TYPE(bd) == failed_leave_chat)
        mx_send_message_handler(info->sock, peer, bd, peer->socket);
    else {
        len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
        uid = get_arr(bd);
        mx_send_msg_clients(info->sock, peer, bd, uid);
        mx_response_db(info, peer,
                       mx_server_msg(bd, " изволил покинуть ваше общество!"));
        free(uid);
    }
    cJSON_Delete(bd);
}
