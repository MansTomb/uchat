#include "libmx.h"

void mx_printstrlen(const char *s, size_t len, const int fd) {
    write(fd, s, len);
}
