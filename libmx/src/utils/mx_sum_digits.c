#include "libmx.h"

int mx_sum_digits(uint64_t num) {
    int sum = 0;

    for (; num; num /= 10)
        sum += num % 10;
    return sum;
}
