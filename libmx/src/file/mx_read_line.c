#include "libmx.h"

int64_t mx_read_line(char **lineptr, char delim, const int fd) {
    size_t len = 0;
    size_t lim = 16;
    size_t checked = 0;

    if (read(fd, NULL, 0) < 0) {
        *lineptr = realloc(*lineptr, 0);
        return -2;
    }
    *lineptr = (char *)realloc(*lineptr, lim);
    for (size_t writen = 1; *lineptr && writen; len += writen) {
        len >= lim ? *lineptr = (char *)realloc(*lineptr, lim *= 2) : NULL;
        checked += (writen = *lineptr ? read(fd, *lineptr + len, 1) : 0);
        if (*lineptr && (*lineptr)[len] == delim)
            break;
    }
    if (*lineptr && (*lineptr = (char *)realloc(*lineptr, len + 1)))
        (*lineptr)[len] = '\0';
    return *lineptr ? (checked ? len : -1) : -2;
}
