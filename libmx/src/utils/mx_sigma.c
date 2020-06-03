#include "libmx.h"

uint64_t mx_sigma(uint64_t n) {
    uint64_t result = 0;

    if (n < 6074001000)
        for (uint64_t i = 1; i <= n; ++i)
            result += i;
    return result;
}
