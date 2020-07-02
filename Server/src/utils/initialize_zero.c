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

char *mx_strjoin_free(const char *s1, const char *s2) {
    char *result;

    if (!s1 && !s2)
        return NULL;
    else if (!s1)
        result = mx_strdup(s2);
    else if (!s2)
        result = mx_strdup(s1);
    else if ((result = malloc(strlen(s1) + strlen(s2) + 1))) {
        strcpy(result, s1);
        strcat(result, s2);
    }
    if (s1)
        mx_strdel((char **)&s1);
    return result;
}
