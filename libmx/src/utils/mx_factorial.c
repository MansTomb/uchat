#include "libmx.h"

uint64_t mx_factorial(uint64_t n) {
    uint64_t result = 1;

    if (n > 20)
        return 0;
    for (uint64_t i = 1; i <= n; ++i)
        result *= i;
    return result;
}
