#include "libmx.h"

void mx_printstr(const char *s, const int fd) {
    write(fd, s, strlen(s));
}
