#include "libmx.h"

int mx_numlen(int64_t nbr, uint32_t base) {
    int result = (nbr < 0 || nbr == 0);

    for (; nbr; nbr /= base)
        ++result;
    return result;
}
