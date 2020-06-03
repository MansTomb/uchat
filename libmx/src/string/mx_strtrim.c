#include "libmx.h"

char *mx_strtrim(const char *str) {
    if (str) {
        int start = 0;
        int end = strlen(str) - 1;
        char *new_str = NULL;

        for (; isspace(str[start]); ++start);
        for (; isspace(str[end]) && end > start; --end);
        new_str = mx_strnew(end > start ? end - start + 1 : 0, '\0');
        strncpy(new_str, str + start, end - start + 1);
        return new_str;
    }
    return NULL;
}
