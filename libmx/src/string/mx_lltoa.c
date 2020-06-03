#include "libmx.h"

static inline char *make_dec(int64_t num, int len) {
    char *str = mx_strnew(len, '\0');

    *str = num < 0 ? '-' : 0;
    for (int j = len - 1; j >= (num <= 0); --j) {
        str[j] = MX_ABS(num % 10) + 48;
        num /= 10;
    }
    return str;
}

char *mx_lltoa(int64_t nbr) {
    return nbr ? make_dec(nbr, mx_numlen(nbr, 10)) : mx_strdup("0");
}
