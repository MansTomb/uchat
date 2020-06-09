#include "libmx.h"

void mx_foreach(void *arr, size_t size, size_t bytes, void(*f)(void *)) {
    if (arr && f && size && bytes) {
        uint8_t *end = (uint8_t *)arr + size * bytes;

        for (uint8_t *i = arr; i < end; i += bytes)
            f(i);
    }
}
