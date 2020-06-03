#include "libmx.h"

static inline char *make_hex(uint64_t nbr, uint64_t length) {
    char *hex = mx_strnew(length, '\0');

    for (int j = length - 1; j >= 0; --j, nbr >>= 4)
        hex[j] = ((nbr % 16) < 10) ? ((nbr % 16) + 48) : ((nbr % 16) + 87);
    return hex;
}

char *mx_ulltoh(uint64_t nbr) {
    return nbr ? make_hex(nbr, mx_unumlen(nbr, 16)) : mx_strdup("0");
}
