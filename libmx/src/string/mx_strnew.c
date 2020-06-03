#include "libmx.h"

char *mx_strnew(const int size, char c) {
    char *ptr = NULL;

    if (size >= 0 && (ptr = (char *)malloc(size + 1))) {
        for (int i = 0; i < size; ++i)
            ptr[i] = c;
        ptr[size] = '\0';
    }
    return ptr;
}
