#include "libmx.h"

static inline char *make_dec(int64_t num, char *str, int len) {
    *str = num < 0 ? '-' : 0;
    for (int j = len - 1; j >= (num <= 0); --j) {
        str[j] = MX_ABS(num % 10) + 48;
        num /= 10;
    }
    return str;
}

char *mx_lltoa_s(int64_t nbr, char *str, int len) {
    return nbr ? make_dec(nbr, str, len) : memset(str, '0', 1);
}
