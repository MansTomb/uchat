#include "server.h"

void mx_db_get_self_response(t_info *info, t_peer *peer, cJSON *get,
                            cJSON *(*func)(sqlite3 *, cJSON *)) {
    cJSON *bd;

    bd = func(info->sock->db, get);
    mx_send_message_handler(info->sock, peer, bd, peer->socket);

    cJSON_Delete(bd);
}
