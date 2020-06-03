#include "libmx.h"

void *mx_memdup(const void *src, size_t n) {
    uint8_t *udst = (uint8_t *)malloc(n);

    if (udst) {
        const uint8_t *usrc = src;

        for (size_t i = 0; i < n; ++i)
            udst[i] = usrc[i];
    }
    return udst;
}
