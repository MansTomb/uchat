#include "libmx.h"

void mx_str_reverse(char *s) {
    if (s) {
        uint64_t j = strlen(s) - 1;

        for (uint64_t i = 0; i < j; ++i, --j)
            mx_swap(s + i, s + j, sizeof(char));
    }
}
