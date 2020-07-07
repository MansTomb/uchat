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

    if (ptype == big_msg || ptype == big_msg_end) {
        p->m_type = ptype;
        p->large_message = mx_strjoin_free(p->large_message, MX_PIECE(get));
        if (ptype == big_msg_end) {
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

    // cJSON_Minify(peer->recv_buff);
    get = cJSON_Parse(peer->recv_buff);
    if (mx_check_err_json(get))
        return;

    type = MX_PTYPE(get);
    if (type == one_msg)
        one_message_handler(info, peer, get);
    else if (type == big_msg || type == big_msg_end)
        mx_large_message_handler(info, peer, get);
    else if (type == file || type == file_end)
        mx_send_file(info->sock, peer, cJSON_Parse(MX_PIECE(get)), peer->socket);   /// затичка
    else
        printf("ERROR p_type\n");

    cJSON_Delete(get);
}
