#include "libmx.h"

static inline char *make_dec(uint64_t num, int len) {
    char *str = mx_strnew(len, '\0');

    for (int j = len - 1; j >= 0; --j) {
        str[j] = (num % 10) + 48;
        num /= 10;
    }
    return str;
}

char *mx_ulltoa(uint64_t nbr) {
    return nbr ? make_dec(nbr, mx_unumlen(nbr, 10)) : mx_strdup("0");
}
