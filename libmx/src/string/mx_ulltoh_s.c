#include "libmx.h"

static inline char *make_hex(uint64_t nbr, char *str, int len) {
    for (int j = len - 1; j >= 0; --j) {
        str[j] = ((nbr % 16) < 10) ? ((nbr % 16) + 48) : ((nbr % 16) + 87);
        nbr /= 16;
    }
    return str;
}

char *mx_ulltoh_s(uint64_t nbr, char *str, int len) {
    return nbr ? make_hex(nbr, str, len) : memset(str, '0', 1);
}
