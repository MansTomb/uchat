#include "server.h"

void mx_db_get_client_contacts(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *bd;

    bd = mx_get_contact_list(info->sock->db, get);
    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_self(info->sock, peer);

    cJSON_Delete(bd);
}
