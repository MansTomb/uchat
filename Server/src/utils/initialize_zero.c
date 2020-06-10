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
