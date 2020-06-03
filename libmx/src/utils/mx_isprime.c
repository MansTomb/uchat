#include "libmx.h"

bool mx_isprime(uint64_t num) {
    if (num < 4)
        return num > 1;
    if (num % 2 == 0 || num % 3 == 0)
        return false;
    for (uint64_t i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    return true;
}
