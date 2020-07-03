#include "server.h"

int mx_check_err_json(cJSON *new) {
    const char *error_ptr;

    if (new == NULL)
        if ((error_ptr = cJSON_GetErrorPtr()) != NULL) {
            fprintf(stderr, "cJSON_Parse error, before: %s", error_ptr);
            return 1;
        }
    return 0;
}

static void one_message_handler(char *receiving_buff) { // переробити під клієнь Антона
    puts(receiving_buff);
    bzero(receiving_buff, sizeof(receiving_buff));
}

static void large_message_handler(char *receiving_buff) { // переробити під клієнь Антона
    // int ptype = MX_PTYPE(get);
    // cJSON *json;

    // if (ptype == 1 || ptype == 2) {
    //     peer->m_type = ptype;
    //     peer->large_message = mx_strjoin_free(peer->large_message, MX_PIECE(get));
    //     if (ptype == 2) {
    //         json = cJSON_Parse(peer->large_message);
    //         if (mx_check_err_json(json))
    //             return;
    //         mx_response_db(info, peer, json);
    //         peer->m_type = 0;
    //         mx_strdel(&peer->large_message);
    //     }
    // }
    // else
    //     printf("ERROR mx_large_message_handler\n");

    sprintf(receiving_buff, "LARGE MESSAGE");
}

void mx_receive_message_handler(char *receiving_buff) {
    cJSON *json;
    int type;

    json = cJSON_Parse(receiving_buff);
    if (mx_check_err_json(json))
        return;

    type = cJSON_GetObjectItem(json, "p_type")->valueint;
    if (type == 0) {            // обробка одного повідомлення розміром до 1024
        one_message_handler(receiving_buff);
    }
    else {                      // обробка одного повідомлення великого розміру
        large_message_handler(receiving_buff);
    }
    cJSON_Delete(json);
}
