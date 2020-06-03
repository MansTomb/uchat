#include "libmx.h"

char *mx_strdup(const char *str) {
    char *ptr = mx_strnew(strlen(str), 0);

    return ptr ? strcpy(ptr, str) : NULL;
}
