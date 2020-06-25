#include "server.h"

void mx_db_send_message(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;
    char *email = NULL;
    int *uid;
    int err;
    int len;

    bd = mx_send_message(info->sock->db, get);
    len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
    uid = malloc(len * sizeof(int));

    for (int i = 0; i < len; ++i) {
        uid[i] = cJSON_GetNumberValue
                (cJSON_GetArrayItem(cJSON_GetObjectItem(bd, "clients_id"), i));
    }
    mx_json_to_sending_buffer(peer, bd);

    if (len == 1) {
        err = mx_send_msg_client(info->sock, peer->sending_buffer, uid[0]);
        if (err == -1) {
            bd = mx_if_message_on_mail(info->sock->db, bd);
        }
    }
    else {
        mx_send_msg_clients(info->sock, peer->sending_buffer, uid, len);
    }
    free(uid);
    cJSON_Delete(bd);
}
