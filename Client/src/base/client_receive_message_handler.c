#include "client.h"

int mx_check_err_json(cJSON *new) {
    const char *error_ptr;

    if (new == NULL)
        if ((error_ptr = cJSON_GetErrorPtr()) != NULL) {
            fprintf(stderr, "cJSON_Parse error, before: %s", error_ptr);
            return 1;
        }
    return 0;
}

static void info_handler(char *str, t_info *info) {
    info->json = cJSON_Parse(str);
    printf("Responce: %s\n", str);
}

static void one_message_handler(char *receiving_buff, t_info *info) {
    cJSON *json = cJSON_Parse(receiving_buff);

    if (mx_check_err_json(json))
        return;
    info_handler(receiving_buff, info);
    bzero(receiving_buff, strlen(receiving_buff));
}

static void large_message_handler(cJSON *json, char **large_message, t_info *info) {
    int ptype = cJSON_GetObjectItem(json, "p_type")->valueint;
    char *piece;
    cJSON *all_json;

    piece = cJSON_GetObjectItem(json, "piece")->valuestring;
    *large_message = mx_strjoin_free(*large_message, piece);
    // puts(*large_message);                            ///test
    if (ptype == 2) {
        // printf("large = %s\n", *large_message);      ///test
        all_json = cJSON_Parse(*large_message);
        if (mx_check_err_json(all_json))
            return;
        info_handler(*large_message, info);
        mx_strdel(large_message);
        cJSON_Delete(all_json);
    }
}

static void file_handler(cJSON *json, char **large_message, t_info *info) {
    // int ptype = cJSON_GetObjectItem(json, "p_type")->valueint;
    // char *piece;
    // cJSON *all_json;

    // piece = cJSON_GetObjectItem(json, "piece")->valuestring;
    // *large_message = mx_strjoin_free(*large_message, piece);
    // // puts(*large_message);                            ///test
    // if (ptype == 2) {
    //     // printf("large = %s\n", *large_message);      ///test
    //     all_json = cJSON_Parse(*large_message);
    //     if (mx_check_err_json(all_json))
    //         return;
    //     info_handler(*large_message, info);
    //     mx_strdel(large_message);
    //     cJSON_Delete(all_json);
    // }

    FILE *new = NULL;
    char buff[MX_MAX_SEND_SIZE];
    char *piece;
    int n;
    int type = cJSON_GetObjectItem(json, "p_type")->valueint;

    if ((new = fopen("new.jpg", "w")) == NULL) {
        printf("Cannot open file new.\n");
        exit(1);
    }
    printf("opened\n");

    while (1) {

        if ((n = read(info->sock->sock, buff, sizeof(buff))) < 0) {
            // perror(MX_ERR_CL_RE);
            puts("\nGood bye, see you soon...\n");
            pthread_exit(0);
        }
        else if (n > 0) {
            printf("%s\n----------------\n", buff);

            json = cJSON_Parse(buff);
            if (mx_check_err_json(json)) {
                // puts(receiving_buff);            ///test
                return;
            }
            type = cJSON_GetObjectItem(json, "p_type")->valueint;
            if (type == 5) {
                // fwrite(*large_message, 1, strlen(*large_message), new);
                // mx_strdel(large_message);
                fclose (new);
                printf("closed\n");
                break;
            }
            else {
                piece = cJSON_GetObjectItem(json, "piece")->valuestring;
                printf("%s\n", piece);
                // *large_message = mx_strjoin_free(*large_message, piece);
                fwrite(piece, 1, cJSON_GetObjectItem(json, "n")->valueint, new);
            }

        }
    }

}

void mx_receive_message_handler(char *receiving_buff, char **large_message,
                                t_info *info) {
    cJSON *json;
    int type;

    json = cJSON_Parse(receiving_buff);
    if (mx_check_err_json(json)) {
        // puts(receiving_buff);            ///test
        return;
    }
    type = cJSON_GetObjectItem(json, "p_type")->valueint;
    if (type == 0) {
        one_message_handler(cJSON_GetObjectItem(json, "piece")->valuestring, info);
    }
    else if (type == 1 || type == 2) {
        // puts(cJSON_Print(json));         ///test
        // puts("111\n");                   ///test
        large_message_handler(json, large_message, info);
    }
    else if (type == 3 || type == 4 || type == 5) {
        file_handler(json, large_message, info);
    }
    else
        printf("receive handler error\n");
    cJSON_Delete(json);
}
