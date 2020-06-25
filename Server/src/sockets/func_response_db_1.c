#include "server.h"

void mx_db_registration(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;

    bd = mx_registration(info->sock->db, get);
    if (MX_TYPE(bd) == success_register)
        peer->uid = MX_VINT(bd, "id");
    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_self(info->sock, peer);

    cJSON_Delete(bd);
}

void mx_db_authorization(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;

    bd = mx_authorization(info->sock->db, get);
    if (MX_TYPE(bd) == success_authorization)
        peer->uid = MX_VINT(bd, "id");
    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_self(info->sock, peer);
    cJSON_Delete(bd);
}

void mx_db_delete(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *responce_bd;

    // responce_bd = mx_registration(info->sock->db, get);
    // mx_json_to_sending_buffer(peer, responce_bd);
    // mx_send_msg_self(info->sock, peer);
    printf("authorization\n");
    // cJSON_Delete(bd);
}

void mx_db_create_personal_chat(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;
    int *cli = malloc(2 * sizeof(int));
    cli[0] = MX_VINT(get, "uid1");
    cli[1] = MX_VINT(get, "uid2");

    bd = mx_create_personal_chat(info->sock->db, get);

    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_clients(info->sock, peer->sending_buffer, cli, 2);
    cJSON_Delete(bd);
    free(cli);
}
