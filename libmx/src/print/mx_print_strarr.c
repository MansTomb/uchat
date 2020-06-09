#include "libmx.h"

void mx_print_strarr(const char **arr, const char *delim, const int fd) {
    if (arr && *arr && delim) {
        for (mx_printstr(*arr, fd); *++arr; mx_printstr(*arr, fd))
            mx_printstr(delim, fd);
        mx_printchar('\n', fd);
    }
}
