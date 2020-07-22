#include "server.h"

void mx_db_get_self_response(t_info *info, t_peer *peer, cJSON *get,
                             cJSON *(*func)(sqlite3 *, cJSON *)) {
    cJSON *bd;

    bd = func(info->sock->db, get);
    mx_send_message_handler(info->sock, peer, bd, peer->socket);

    cJSON_Delete(bd);
}

static void active_users(t_info *info, cJSON *arr) {
    int len;
    cJSON *item;
    int uid;

    len = cJSON_GetArraySize(arr);
    for (int j = 0; j < len; ++j) {
        item = cJSON_GetArrayItem(arr, j);
        uid = MX_VINT(item, "coid");

        for (int i = 0; i < MAX_CLIENTS; ++i) {
            int sd = info->sock->connection_list[i].socket;
            if (sd != MX_NO_SOCKET)
                if (info->sock->connection_list[i].uid == uid) {
                    cJSON_DeleteItemFromObject(item, "active");
                    cJSON_AddBoolToObject(item, "active", true);
                    break;
                }
        }
    }
}

void mx_db_get_contact_list(t_info *info, t_peer *peer, cJSON *get) {
    cJSON *bd;
    cJSON *arr;

    bd = mx_get_contact_list(info->sock->db, get);
    arr = cJSON_GetObjectItem(bd, "contacts");
    active_users(info, arr);

    mx_send_message_handler(info->sock, peer, bd, peer->socket);

    cJSON_Delete(bd);
}
