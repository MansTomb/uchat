#include "libmx.h"

void mx_swap(void *restrict v1, void *restrict v2, size_t size) {
    if (v1 && v2 && v1 != v2) {
        uint8_t temp[size];

        memcpy(temp, v1, size);
        memcpy(v1, v2, size);
        memcpy(v2, temp, size);
    }
}
