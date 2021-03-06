#include "server.h"

static void send_on_email(t_info *info, t_peer *peer, cJSON *bd) {
    char *email = NULL;
    int *uid;
    int len;
    int err;

    len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
    uid = mx_get_arr(bd);
    if (len == 1 && MX_TYPE(bd) != superuser_message) {
        err = mx_send_msg_client(info->sock, peer, bd, uid[0]);
        if (err == -1)
            bd = mx_if_message_on_mail(info->sock->db, bd);
    }
    else
        mx_send_msg_clients(info->sock, peer, bd, uid);
    free(uid);
}

int *mx_get_arr(cJSON *bd) {
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

void mx_db_send_message(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;

    if (MX_TYPE(get) == superuser_message)
        bd = mx_superuser_message(info->sock->db, get);
    else
        bd = mx_send_message(info->sock->db, get);
    if (MX_TYPE(bd) == failed_send_message) {
        // printf("%s", cJSON_Print(bd));
        mx_send_message_handler(info->sock, peer, bd, peer->socket);
        mx_send_message_handler(info->sock, peer, mx_su_msg(bd,
            " - не может писать в этом чате!"), peer->socket);
    }
    else
        send_on_email(info, peer, bd);
    if (MX_VSTR(get, "content")[0] == '/')
        mx_db_commands(info, peer, get);
    cJSON_Delete(bd);
}

void mx_db_edit_message(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;
    int *uid;
    int err;
    int len;

    bd = mx_edit_message(info->sock->db, get);
    len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
    uid = mx_get_arr(bd);
    mx_send_msg_clients(info->sock, peer, bd, uid);

    free(uid);
    cJSON_Delete(bd);
}
