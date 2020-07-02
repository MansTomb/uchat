#include "server.h"

void mx_db_registration(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;

    bd = mx_registration(info->sock->db, get);
    if (MX_TYPE(bd) == success_register)
        peer->uid = MX_VINT(bd, "id");
    mx_send_message_handler(info->sock, peer, bd, peer->socket);

    cJSON_Delete(bd);
}

void mx_db_authorization(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;

    bd = mx_authorization(info->sock->db, get);
    if (MX_TYPE(bd) == success_authorization) {
        peer->uid = MX_VINT(bd, "id");
        mx_message_on_mail(MX_VSTR(bd, "email"), MX_EMAIL_PATH_LOGIN);
    }
    mx_send_message_handler(info->sock, peer, bd, peer->socket);
    cJSON_Delete(bd);
}

void mx_db_delete(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *responce_bd;

    // responce_bd = mx_registration(info->sock->db, get);
    // mx_send_msg_self(info->sock, peer, );
    printf("authorization\n");
    // cJSON_Delete(bd);
}

void mx_db_create_personal_chat(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;
    int *cli = malloc(3 * sizeof(int));
    cli[0] = MX_VINT(get, "uid1");
    cli[1] = MX_VINT(get, "uid2");
    cli[2] = -1;

    bd = mx_create_personal_chat(info->sock->db, get);
    mx_send_msg_clients(info->sock, peer, bd, cli);
    cJSON_Delete(bd);
    free(cli);
}
