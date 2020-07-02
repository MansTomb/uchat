#include "server.h"

static int one_message_handler(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *piece;

    piece = cJSON_Parse(MX_VSTR(get, "piece"));
    if (mx_check_err_json(piece))
        return -1;
    mx_response_db(info, peer, piece);
    return 0;
}

void mx_large_message_handler(t_info *info, t_peer *peer, cJSON *get) {
    int ptype = MX_PTYPE(get);
    cJSON *json;

    if (ptype == 1 || ptype == 2) {
        peer->m_type = ptype;
        peer->large_message = mx_strjoin_free(peer->large_message, MX_PIECE(get));
        if (ptype == 2) {
            json = cJSON_Parse(peer->large_message);
            if (mx_check_err_json(json))
                return;
            mx_response_db(info, peer, json);
            peer->m_type = 0;
            mx_strdel(&peer->large_message);
        }
    }
    else
        printf("ERROR mx_large_message_handler\n");
}

void mx_message_handler(t_info *info, t_peer *peer) {
    cJSON *get;
    int type;

    get = cJSON_Parse(peer->receiving_buffer);
    if (mx_check_err_json(get))
        return;

    type = MX_PTYPE(get);
    if (type == 0)
        one_message_handler(info, peer, get);
    else
        mx_large_message_handler(info, peer, get);
    cJSON_Delete(get);
}
