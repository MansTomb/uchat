#include "server.h"

static void send_on_email(t_info *info, t_peer *peer, cJSON *bd, int uidzero) {
    int err;

    err = mx_send_msg_client(info->sock, peer, bd, uidzero);
    if (err == -1)
        bd = mx_if_message_on_mail(info->sock->db, bd);
}

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

void mx_db_send_message(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;
    char *email = NULL;
    int *uid;
    int len;

    if (MX_TYPE(bd) == superuser_message)
        bd = mx_superuser_message(info->sock->db, get);
    else
        bd = mx_send_message(info->sock->db, get);
    if (MX_TYPE(bd) == failed_send_message) {
        // printf("%s", cJSON_Print(bd));
        mx_send_message_handler(info->sock, peer, bd, peer->socket);
        mx_response_db(info, peer, mx_server_msg(bd,
                       "Вы забанены или не можете писать в этом чате!"));
    }
    else {
        len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
        uid = get_arr(bd);
        if (len == 1 && MX_TYPE(bd) != superuser_message)
            send_on_email(info, peer, bd, uid[0]);
        else
            mx_send_msg_clients(info->sock, peer, bd, uid);
        free(uid);
    }
    cJSON_Delete(bd);
}

void mx_db_edit_message(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;
    int *uid;
    int err;
    int len;

    bd = mx_edit_message(info->sock->db, get);
    len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
    uid = get_arr(bd);
    mx_send_msg_clients(info->sock, peer, bd, uid);

    free(uid);
    cJSON_Delete(bd);
}
