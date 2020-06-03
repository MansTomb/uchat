#include "libmx.h"

void mx_printunum(uint64_t n, const int fd) {
    if (n > 9)
        mx_printunum(n / 10, fd);
    mx_printchar(n % 10 + 48, fd);
}
