#include "server.h"

static int check_err_json(cJSON *new) {
    const char *error_ptr;

    if (new == NULL)
        if ((error_ptr = cJSON_GetErrorPtr()) != NULL) {
            fprintf(stderr, "cJSON_Parse error, before: %s", error_ptr);
            return 1;
        }
    return 0;
}

void mx_message_handler(t_info *info, t_peer *peer) {
    cJSON *get;
    int type;

    get = cJSON_Parse(peer->receiving_buffer);
    if (check_err_json(get))
        return;

    type = (int)cJSON_GetNumberValue(cJSON_GetObjectItem(get, "json_type"));
    printf("%d\n", type);

    mx_response_db(info, peer, type, get);
}


static void registraion(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *responce_bd;

    responce_bd = mx_registration(info->sock->db, get);
    mx_json_to_sending_buffer(peer, responce_bd);
    mx_send_msg_self(info->sock, peer);
}

static void authorization(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *responce_bd;

    // responce_bd = mx_registration(info->sock->db, get);
    // mx_json_to_sending_buffer(peer, responce_bd);
    // mx_send_msg_self(info->sock, peer);
    printf("authorization\n");
}

static void deletion(t_info *info, t_peer *peer, int type, cJSON *get) {
    cJSON *responce_bd;

    // responce_bd = mx_registration(info->sock->db, get);
    // mx_json_to_sending_buffer(peer, responce_bd);
    // mx_send_msg_self(info->sock, peer);
    printf("authorization\n");
}

void mx_response_db(t_info *info, t_peer *peer, int type, cJSON *get) {

    switch (type) {
    case mx_make_register:
        registraion(info, peer, type, get);
        break;
    case mx_make_authorization:
        authorization(info, peer, type, get);
        break;
    case mx_make_deletion:
        deletion(info, peer, type, get);
        break;
    case mx_send_message:
        printf("mx_send_message\n");
        break;
    default:
        printf("unknown type of message\n");
        break;
    }
}
