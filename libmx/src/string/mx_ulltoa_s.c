#include "libmx.h"

static inline char *make_dec(uint64_t num, char *str, int len) {
    for (int j = len - 1; j >= 0; --j) {
        str[j] = (num % 10) + 48;
        num /= 10;
    }
    return str;
}

char *mx_ulltoa_s(uint64_t nbr, char *str, int len) {
    return nbr ? make_dec(nbr, str, len) : memset(str, '0', 1);
}
