#include "client.h"

static int mx_check_err_json(cJSON *new) {
    const char *error_ptr;

    if (new == NULL)
        if ((error_ptr = cJSON_GetErrorPtr()) != NULL) {
            fprintf(stderr, "cJSON_Parse error, before: %s", error_ptr);
            return 1;
        }
    return 0;
}

static void info_handler(char *str) { // переробити під клієнт Антона
    puts(str);        // вивід в термінал
}

static void one_message_handler(char *receiving_buff) {
    cJSON *json = cJSON_Parse(receiving_buff);

    if (mx_check_err_json(json))
        return;
    info_handler(receiving_buff);
    bzero(receiving_buff, strlen(receiving_buff));
}

static void large_message_handler(cJSON *json, char **large_message) {
    int ptype = cJSON_GetObjectItem(json, "p_type")->valueint;
    char *piece;
    cJSON *all_json;

    if (ptype == 1 || ptype == 2) {
        piece = cJSON_GetObjectItem(json, "piece")->valuestring;
        *large_message = mx_strjoin_free(*large_message, piece);
        // puts(*large_message);                            ///test
        if (ptype == 2) {
            // printf("large = %s\n", *large_message);      ///test
            all_json = cJSON_Parse(*large_message);
            if (mx_check_err_json(all_json))
                return;
            info_handler(*large_message);
            mx_strdel(large_message);
            cJSON_Delete(all_json);
        }
    }
    else
        printf("ERROR large_message_handler\n");
}

void mx_receive_message_handler(char *receiving_buff, char **large_message) {
    cJSON *json;
    int type;

    json = cJSON_Parse(receiving_buff);
    if (mx_check_err_json(json)) {
        // puts(receiving_buff);            ///test
        return;
    }
    type = cJSON_GetObjectItem(json, "p_type")->valueint;
    if (type == 0) {
        one_message_handler(cJSON_GetObjectItem(json, "piece")->valuestring);
    }
    else if (type == 1 || type == 2) {
        // puts(cJSON_Print(json));         ///test
        // puts("111\n");                   ///test
        large_message_handler(json, large_message);
    }
    else {
        printf("ERROR type\n");
    }
    cJSON_Delete(json);
}
