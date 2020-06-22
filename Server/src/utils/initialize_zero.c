#include "server.h"

void mx_initialize_zero_int_arr(int *arr, int size) {
    for (int i = 0; i < size; ++i)
        arr[i] = 0;
}

void mx_strip_newline(char *s) {
    while (*s != '\0') {
        if (*s == '\r' || *s == '\n') {
            *s = '\0';
        }
        s++;
    }
}

void mx_json_to_sending_buffer(t_peer *peer, cJSON *json) {
    char *root = cJSON_Print(json);

    sprintf(peer->sending_buffer, "%s", root);
    printf("%s\n", peer->sending_buffer);
    // cJSON_Delete(json);
}
