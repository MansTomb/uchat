#include "server.h"

void mx_db_get_self_response(t_info *info, t_peer *peer, cJSON *get,
                            cJSON *(*func)(sqlite3 *, cJSON *)) {
    cJSON *bd;

    bd = func(info->sock->db, get);
    mx_json_to_sending_buffer(peer, bd);
    mx_send_msg_self(info->sock, peer);

    cJSON_Delete(bd);
}
