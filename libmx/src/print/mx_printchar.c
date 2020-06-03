#include "libmx.h"

void mx_printchar(char c, const int fd) {
    write(fd, &c, 1);
}
