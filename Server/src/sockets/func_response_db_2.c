#include "server.h"

static void send_on_email(t_info *info, t_peer *peer, cJSON *bd, int uidzero) {
    int err;

    err = mx_send_msg_client(info->sock, peer, bd, uidzero);
    if (err == -1)
        bd = mx_if_message_on_mail(info->sock->db, bd);
}

void mx_db_send_message(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;
    char *email = NULL;
    int *uid;
    int len;

    bd = mx_send_message(info->sock->db, get);
    if (MX_VINT(bd, "role") == -1)
        // printf("%s", cJSON_Print(bd));
        mx_send_message_handler(info->sock, peer, bd, peer->socket);
    else {
        len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
        uid = malloc((len + 1) * sizeof(int));
        for (int i = 0; i < len; ++i)
            uid[i] = cJSON_GetNumberValue
                    (cJSON_GetArrayItem(cJSON_GetObjectItem(bd, "clients_id"), i));
        uid[len] = -1;
        if (len == 1)
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
    uid = malloc((len + 1) * sizeof(int));

    for (int i = 0; i < len; ++i) {
        uid[i] = cJSON_GetNumberValue
                (cJSON_GetArrayItem(cJSON_GetObjectItem(bd, "clients_id"), i));
    }
    uid[len] = -1;
    mx_send_msg_clients(info->sock, peer, bd, uid);

    free(uid);
    cJSON_Delete(bd);
}

void mx_db_invite_send_message(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;
    int *uid;
    int len;

    bd = mx_invite(info->sock->db, get);
    // printf("%s", cJSON_Print(bd));

    len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
    uid = malloc((len + 1) * sizeof(int));
    for (int i = 0; i < len; ++i)
        uid[i] = cJSON_GetNumberValue
                (cJSON_GetArrayItem(cJSON_GetObjectItem(bd, "clients_id"), i));
    uid[len] = -1;
    // cJSON_Delete(bd, "clients_id");
    if (MX_TYPE(bd) == failed_add_user_in_chat)
        mx_send_message_handler(info->sock, peer, bd, peer->socket);
    else {
        mx_send_msg_clients(info->sock, peer, bd, uid);
        // отправить добавление чата тому кого добавляют
    }
    free(uid);

    cJSON_Delete(bd);
}
