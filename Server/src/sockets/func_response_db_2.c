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
        for (int i = 0; i < len; ++i) {
            mx_send_msg_client(info->sock, peer->sending_buffer, uid[i]);
            printf("111\n");
        }
    }
    cJSON_Delete(bd);
}

void mx_db_update_profile(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;

    bd = mx_update_profile(info->sock->db, get);
    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_self(info->sock, peer);

    cJSON_Delete(bd);
}

void mx_db_add_new_contact(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;

    bd = mx_add_new_contact(info->sock->db, get);
    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_self(info->sock, peer);

    cJSON_Delete(bd);
}

void mx_db_del_contact(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;

    bd = mx_del_contact(info->sock->db, get);
    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_self(info->sock, peer);

    cJSON_Delete(bd);
}
