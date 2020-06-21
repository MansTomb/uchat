#include "server.h"

void mx_db_send_message(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;
    char *email = NULL;
    int *uid;
    int err;

    bd = mx_send_message(info->sock->db, get);
    // printf("%s\n", cJSON_Print(bd));

    int len = cJSON_GetArraySize(cJSON_GetObjectItem(bd, "clients_id"));
    uid = malloc(len * sizeof(int));

    for (int i = 0; i < len; ++i) {
        uid[i] = cJSON_GetNumberValue
                (cJSON_GetArrayItem(cJSON_GetObjectItem(bd, "clients_id"), i));
        printf("uid = %d\n", uid[i]);
    }

    mx_json_to_sending_buffer(peer, bd);

    if (len == 1) {
        err = mx_send_msg_client(info->sock, peer->sending_buffer, uid[0]);
        if (err == -1) {
            // email = cJSON_GetObjectItem(bd, "email")->valuestring;
            // mx_message_on_mail(email);
        }
    }
    else {
        for (int i = 0; i < len; ++i) {
            mx_send_msg_client(info->sock, peer->sending_buffer, uid[i]);
            printf("111\n");
        }
    }



    // mx_send_msg_number_of_clients(info->sock, peer->sending_buffer, cli);
    // mx_send_msg_client(info->sock, peer->sending_buffer, cli);
    cJSON_Delete(bd);
}
