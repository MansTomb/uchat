#include "server.h"

void mx_db_registration(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;

    bd = mx_registration(info->sock->db, get);
    if (cJSON_GetObjectItem(bd, "json_type")->valueint == success_register)
        peer->uid = cJSON_GetObjectItem(bd, "id")->valueint;
    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_self(info->sock, peer);

    cJSON_Delete(bd);
}

void mx_db_authorization(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;

    bd = mx_authorization(info->sock->db, get);
    if (cJSON_GetObjectItem(bd, "json_type")->valueint == success_authorization)
        peer->uid = cJSON_GetObjectItem(bd, "id")->valueint;
    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_self(info->sock, peer);
    cJSON_Delete(bd);
}

void mx_db_delete(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *responce_bd;

    // responce_bd = mx_registration(info->sock->db, get);
    // mx_json_to_sending_buffer(peer, responce_bd);
    // mx_send_msg_self(info->sock, peer);
    printf("authorization\n");
    // cJSON_Delete(bd);
}

void mx_db_change_password(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;

    bd = mx_change_password(info->sock->db, get);
    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_self(info->sock, peer);
    cJSON_Delete(bd);
}

void mx_db_create_personal_chat(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;
    int *cli = malloc(2 * sizeof(int));
    cli[0] = cJSON_GetObjectItem(get, "uid1")->valueint;
    cli[1] = cJSON_GetObjectItem(get, "uid2")->valueint;
    // printf("peer1 = %d, peer2 = %d\n", cli[0], cli[1]);

    bd = mx_create_personal_chat(info->sock->db, get);

    // if (cJSON_GetObjectItem(bd, "json_type")->valueint == success_authorization)
    //     peer->uid = cJSON_GetObjectItem(bd, "id")->valueint;
    // printf("peer uid = %d\n", peer->uid);

    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_number_of_clients(info->sock, peer->sending_buffer, cli);
    cJSON_Delete(bd);
    free(cli);
}
