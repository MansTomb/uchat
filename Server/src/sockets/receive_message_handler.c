#include "server.h"

static int one_message_handler(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *piece;

    piece = cJSON_Parse(MX_VSTR(get, "piece"));
    if (mx_check_err_json(piece))
        return -1;
    mx_response_db(info, peer, piece);
    return 0;
}

void mx_large_message_handler(t_info *info, t_peer *p, cJSON *get) {
    int ptype = MX_PTYPE(get);
    cJSON *json;

    if (ptype == 1 || ptype == 2) {
        p->m_type = ptype;
        p->large_message = mx_strjoin_free(p->large_message, MX_PIECE(get));
        if (ptype == 2) {
            json = cJSON_Parse(p->large_message);
            if (mx_check_err_json(json))
                return;
            mx_response_db(info, p, json);
            p->m_type = 0;
            mx_strdel(&p->large_message);
        }
    }
    else
        printf("ERROR mx_large_message_handler\n");
}

void mx_receive_message_handler(t_info *info, t_peer *peer) {
    cJSON *get;
    int type;

    get = cJSON_Parse(peer->receiving_buffer);
    if (mx_check_err_json(get))
        return;

    type = MX_PTYPE(get);
    if (type == 0)
        one_message_handler(info, peer, get);
    else if (type == 1 || type == 2)
        mx_large_message_handler(info, peer, get);
    else
        printf("ERROR p_type\n");

    cJSON_Delete(get);
}
