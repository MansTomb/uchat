#include "libmx.h"

void mx_reverse_vector(t_vector *v) {
    if (v && v->size && v->arr) {
        uint8_t *i = v->arr;
        uint8_t *j = v->arr + (v->size - 1) * v->bytes;

        for (size_t b = v->bytes; i < j; i += b, j -= b)
            mx_swap(i, j, b);
    }
}
