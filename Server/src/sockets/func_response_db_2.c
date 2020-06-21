#include "server.h"

void mx_db_send_message(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;
    // int *cli = malloc(2 * sizeof(int));
    // cli[0] = cJSON_GetObjectItem(get, "uid1")->valueint;
    // cli[1] = cJSON_GetObjectItem(get, "uid2")->valueint;
    // printf("peer1 = %d, peer2 = %d\n", cli[0], cli[1]);

    bd = mx_send_message(info->sock->db, get);

    // if (cJSON_GetObjectItem(bd, "json_type")->valueint == success_authorization)
    //     peer->uid = cJSON_GetObjectItem(bd, "id")->valueint;
    // printf("peer uid = %d\n", peer->uid);

    mx_json_to_sending_buffer(peer, bd);
    // mx_send_msg_client(info->sock, peer->sending_buffer, cli);
}
